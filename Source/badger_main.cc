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

#include <QApplication>
#include <QFileInfo>
#include <QtDebug>

#include "badger.h"

int main(int argc, char *argv[])
{
  QString account_image("");
  QString account_image_size("");
  QString background("");
  QString date_time_format("");
  QString logo("");
  QString output("");
  auto enable_shortcuts = false;
  auto show_date_time = false;

  for(int i = 0; i < argc; i++)
    if(!argv || !argv[i])
      continue;
    else if(strcmp(argv[i], "--account-image") == 0)
      {
	if(i++ >= argc)
	  continue;

	if(argv[i])
	  account_image = argv[i];
      }
    else if(strcmp(argv[i], "--account-image-size") == 0)
      {
	if(i++ >= argc)
	  continue;

	if(argv[i])
	  account_image_size = argv[i];
      }
    else if(strcmp(argv[i], "--background") == 0)
      {
	if(i++ >= argc)
	  continue;

	if(argv[i])
	  background = argv[i];
      }
    else if(strcmp(argv[i], "--background-color") == 0)
      {
	if(i++ >= argc)
	  continue;

	if(argv[i])
	  background = argv[i];
      }
    else if(strcmp(argv[i], "--date-time-format") == 0)
      {
	if(i++ >= argc)
	  continue;

	if(argv[i])
	  date_time_format = argv[i];
      }
    else if(strcmp(argv[i], "--enable-shortcuts") == 0)
      enable_shortcuts = true;
    else if(strcmp(argv[i], "--logo-image") == 0)
      {
	if(i++ >= argc)
	  continue;

	if(argv[i])
	  logo = argv[i];
      }
    else if(strcmp(argv[i], "--output") == 0)
      {
	if(i++ >= argc)
	  continue;

	if(argv[i])
	  output = argv[i];
      }
    else if(strcmp(argv[i], "--show-date-time") == 0)
      show_date_time = true;

  if(!QFileInfo(account_image).isReadable())
    {
      qDebug() << argv[0] << ":" << "cannot read account-image file.";
      return EXIT_FAILURE;
    }

  QApplication application(argc, argv);
  badger badger(nullptr);

  badger.enable_shortcuts(enable_shortcuts);
  badger.set_account_icon(QIcon(account_image));
  badger.set_account_icon_size
    (QSize(qBound(0, account_image_size.split(',').value(0).toInt(), 128),
	   qBound(0, account_image_size.split(',').value(1).toInt(), 128)));
  badger.set_background(background);
  badger.set_background_color(background);
  badger.set_date_time_format(date_time_format);
  badger.set_logo(logo);
  badger.set_output(output);
  badger.set_show_date_time(show_date_time);
  badger.showFullScreen();
  return application.exec();
}
