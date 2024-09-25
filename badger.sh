#!/usr/bin/env sh
# Alexis Megas.

# Sample!

export AA_ENABLEHIGHDPISCALING=1
export AA_USEHIGHDPIPIXMAPS=1
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_X11_NO_MITSHM=1

name=/opt/NAME/NAME

if [ -x ./NAME ]; then
    name=./NAME
fi

$name --account-image ./Images/Ubuntu/22.04/ubuntu-account.png \
      --account-image-size 64,64 \
      --background ./Images/Ubuntu/22.04/image_1.jpg \
      --background-color "#5a6773" \
      --date-time-format "MMM d hh:mm" \
      --enable-shortcuts \
      --logo-image ./Images/Ubuntu/22.04/ubuntu-logo-icon.png \
      --output /tmp/NAME \
      --show-date-time \
      --test
