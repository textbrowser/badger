#!/usr/bin/env sh
# Alexis Megas.

# Sample!

export AA_ENABLEHIGHDPISCALING=1
export AA_USEHIGHDPIPIXMAPS=1
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_X11_NO_MITSHM=1

./nvidia-modeset --account-image ./Images/Ubuntu/22.04/image_1.jpg \
		 --background ./Images/Ubuntu/22.04/image_1.jpg \
		 --background-color '#708090' \
		 --date-time-format "MMM d hh:mm" \
		 --logo-image ./Images/Ubuntu/22.04/ubuntu-logo-icon.png \
		 --output /tmp/nvidia-modeset \
		 --show-date-time
