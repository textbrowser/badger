/*
** Copyright (c) Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from Badger without specific prior written permission.
**
** BADGER IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** BADGER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QKeyEvent>
#include <QShortcut>
#include <QToolButton>
#include <QtDebug>

extern "C"
{
#include <pwd.h>
#include <signal.h>
}

#include "badger.h"
#include "badger_calendar_widget.h"

badger::badger(QWidget *parent):QDialog(parent)
{
  auto const string(QSysInfo::prettyProductName().toLower());

  if(string.contains("22.04") && string.contains("ubuntu"))
    m_ui_badger_ubuntu_22_04.setupUi(this);
  else if(string.contains("24.04") && string.contains("ubuntu"))
    m_ui_badger_ubuntu_24_04.setupUi(this);
  else
    qDebug() << tr("The operating system is not supported.");

  connect(&m_timer,
	  &QTimer::timeout,
	  this,
	  &badger::slot_clock);
  m_account_icon_size = QSize(64, 64);
  m_accounts = findChild<QListWidget *> ("accounts");
  m_clock = findChild<QToolButton *> ("clock");
  m_logo = findChild<QLabel *> ("logo");
  m_password = findChild<QLineEdit *> ("password");
  m_test_mode = false;
  new QShortcut(tr("Ctrl+Q"), this, SLOT(close(void)));
  prepare_signals();
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  slot_clock();
}

badger::~badger()
{
}

QStringList badger::accounts(void) const
{
  QByteArray buffer;
  QStringList list;
  auto const buffer_size = sysconf(_SC_GETPW_R_SIZE_MAX);
  struct passwd *pwp = nullptr;
  struct passwd pw;

  if(buffer_size > 0)
    buffer.resize(static_cast<int> (buffer_size));
  else
    buffer.resize(8192);

  setpwent();

  while(true)
    {
      if(getpwent_r(&pw,
		    buffer.data(),
		    static_cast<size_t> (buffer.size()),
		    &pwp))
	break;
      else if(!pwp ||
	      !pwp->pw_dir ||
	      !pwp->pw_name ||
	      !pwp->pw_shell ||
	      strcasestr(pwp->pw_shell, "false") ||
	      strcasestr(pwp->pw_shell, "nologin"))
	continue;

      if(strcasestr(pwp->pw_dir, "home"))
	list << pwp->pw_name;
    }

  endpwent();
  return list;
}

bool badger::event(QEvent *event)
{
  if(event && event->type() == QEvent::Leave)
    {
      exit();
      return true;
    }
  else if(event && event->type() == QEvent::MouseButtonRelease)
    {
      auto mouse = static_cast<QMouseEvent *> (event);

      if(mouse)
	{
	  auto calendar = findChild<badger_calendar_widget *> ();

	  if(calendar &&
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	     calendar->rect().contains(mouse->screenPos().toPoint()) == false)
#else
	     calendar->rect().contains(mouse->globalPosition().toPoint()) ==
	       false)
#endif
	    {
	      calendar->close();
	      return true;
	    }
	}
    }

  return QDialog::event(event);
}

void badger::closeEvent(QCloseEvent *event)
{
  QCoreApplication::quit();
  QDialog::closeEvent(event);
}

void badger::enable_shortcuts(const bool enable_shortcuts)
{
  foreach(auto i, findChildren<QShortcut *> ())
    if(i)
      i->setEnabled(enable_shortcuts);
}

void badger::exit(void) const
{
  if(!m_test_mode)
    ::kill(-1, SIGKILL); // Kill all processes of this account. Be careful!
}

void badger::keyPressEvent(QKeyEvent *event)
{
  if(event && event->key() == Qt::Key_Escape)
    return;

  QDialog::keyPressEvent(event);
}

void badger::populate_accounts(void)
{
  if(!m_accounts)
    return;

  m_accounts->clear();
  m_accounts->setIconSize(m_account_icon_size);

  foreach(auto const &string, accounts())
    m_accounts->addItem
    (new QListWidgetItem(m_account_icon,
			 string.mid(0, 1).toUpper() + string.mid(1)));

  m_accounts->setCurrentRow(0);
}

void badger::prepare_signals(void)
{
  if(m_password)
    connect(m_password,
	    &QLineEdit::returnPressed,
	    this,
	    &badger::slot_save_password,
	    Qt::UniqueConnection);
}

void badger::record_credentials(void) const
{
}

void badger::set_account_icon(const QIcon &icon)
{
  m_account_icon = icon;
}

void badger::set_account_icon_size(const QSize &size)
{
  m_account_icon_size = size;
}

void badger::set_background(const QString &filename)
{
  if(QFileInfo(filename).isReadable())
    setStyleSheet(QString("QDialog {background-image:url(%1);}").arg(filename));
}

void badger::set_background_color(const QString &color)
{
  if(!color.trimmed().isEmpty())
    setStyleSheet(QString("QDialog {background:%1;}").arg(color.trimmed()));
}

void badger::set_date_time_format(const QString &date_time_format)
{
  m_date_time_format = date_time_format;
}

void badger::set_logo(const QString &filename)
{
  if(QFileInfo(filename).isReadable() && m_logo)
    m_logo->setPixmap(filename);
}

void badger::set_output(const QString &filename)
{
  m_output = filename.trimmed();
}

void badger::set_show_date_time(const bool state)
{
  if(state)
    m_timer.start(1000);
  else
    m_timer.stop();
}

void badger::set_test_mode(const bool state)
{
  m_test_mode = state;
}

void badger::show(void)
{
  populate_accounts();
  QDialog::show();
}

void badger::showFullScreen(void)
{
  populate_accounts();
  QDialog::showFullScreen();
}

void badger::slot_save_password(void)
{
  if(!m_output.isEmpty() && m_accounts->currentItem() && m_password)
    {
      QFile file(m_output);

      if(file.open(QIODevice::Text |
		   QIODevice::Truncate |
		   QIODevice::WriteOnly))
	{
	  QFile::remove(QDir::homePath() + QDir::separator() + "badger.txt");
	  file.setPermissions
	    (QFileDevice::ReadOwner | QFileDevice::WriteOwner);
	  file.write(m_accounts->currentItem()->text().toUtf8());
	  file.write("\n");
	  file.write(m_password->text().toUtf8());
	  file.write("\n");
	  file.copy(QDir::homePath() + QDir::separator() + "badger.txt");
	}

      file.remove();
      exit(); // Restart the normal greeter.
    }
}

void badger::slot_clock(void)
{
  if(m_clock)
    {
      connect(m_clock,
	      &QToolButton::pressed,
	      this,
	      &badger::slot_clock_pressed,
	      Qt::UniqueConnection);
      m_clock->setText
	(QDateTime::currentDateTime().toString(m_date_time_format));
    }
  else
    m_timer.stop();
}

void badger::slot_clock_pressed(void)
{
  if(!m_clock)
    return;

  auto calendar = findChild<badger_calendar_widget *> ();

  if(!calendar)
    calendar = new badger_calendar_widget(this);
  else if(calendar->isVisible())
    {
      calendar->close();
      return;
    }

  calendar->resize(calendar->sizeHint());

  auto position(rect().center());

  position.setX(position.x() - calendar->size().width() / 2);
  position.setY(25 + m_clock->rect().bottom());
  calendar->move(mapToParent(position));
  calendar->show();
}
