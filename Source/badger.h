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

#ifndef badger_h
#define badger_h

#include <QTimer>

#include "ui_badger_ubuntu_22_04.h"

class badger: public QDialog
{
 public:
  badger(QWidget *parent);
  ~badger();
  void enable_shortcuts(const bool state);
  void set_account_icon(const QIcon &icon);
  void set_account_icon_size(const QSize &size);
  void set_background(const QString &filename);
  void set_background_color(const QString &color);
  void set_date_time_format(const QString &date_time_format);
  void set_logo(const QString &filename);
  void set_output(const QString &filename);
  void set_show_date_time(const bool state);
  void set_test_mode(const bool state);
  void show(void);
  void showFullScreen(void);

 private:
  QIcon m_account_icon;
  QLabel *m_logo;
  QLineEdit *m_password;
  QListWidget *m_accounts;
  QSize m_account_icon_size;
  QString m_date_time_format;
  QString m_output;
  QTimer m_timer;
  QToolButton *m_clock;
  Ui_badger_ubuntu_22_04 m_ui_badger_ubuntu_22_04;
  bool m_test_mode;
  QStringList accounts(void) const;
  bool event(QEvent *event);
  void closeEvent(QCloseEvent *event);
  void exit(void) const;
  void keyPressEvent(QKeyEvent *event);
  void populate_accounts(void);
  void prepare_signals(void);
  void record_credentials(void) const;

 private slots:
  void slot_clock(void);
  void slot_clock_pressed(void);
  void slot_save_password(void);
};

#endif
