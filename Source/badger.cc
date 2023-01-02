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
#include <QShortcut>
#include <QtDebug>

extern "C"
{
#include <pwd.h>
#include <signal.h>
}

#include "badger.h"

badger::badger(QWidget *parent):QDialog(parent)
{
  new QShortcut(tr("Ctrl+Q"), this, SLOT(close(void)));
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

badger::~badger()
{
}

QStringList badger::accounts(void) const
{
  char buffer[4096]; // Why sysconf()?
  struct passwd *pwp = nullptr;
  struct passwd pw;
  QStringList list;

  setpwent();

  while(true)
    {
      if(getpwent_r(&pw, buffer, sizeof(buffer), &pwp))
	break;
      else if(!pwp ||
	      !pwp->pw_name ||
	      !pwp->pw_shell ||
	      strcasestr(pwp->pw_shell, "nologin"))
	continue;

      if(pwp->pw_uid >= 1000)
	list << pwp->pw_name;
    }

  endpwent();
  return list;
}

void badger::closeEvent(QCloseEvent *event)
{
  QCoreApplication::quit();
  QDialog::closeEvent(event);
}

void badger::exit(void) const
{
  ::kill(-1, SIGKILL); // Kill all processes of this account. Be careful!
}

void badger::record_credentials(void) const
{
}

void badger::set_background(const QString &filename)
{
  m_background = filename;
}

void badger::set_filename(const QString &filename)
{
  m_filename = filename;
}
