#!/usr/bin/env sh

# Alexis Megas.

set_qt_qpa_platformtheme()
{
    qt6=$(ldd "$1" 2>/dev/null | grep Qt6 2>/dev/null)

    if [ ! -z "$qt6" ]
    then
	if [ ! -z "$(which qt6ct)" ]
	then
	    echo "Exporting QT_QPA_PLATFORMTHEME as qt6ct."

	    export QT_QPA_PLATFORMTHEME=qt6ct
	fi
    fi
}

export AA_ENABLEHIGHDPISCALING=1
export AA_USEHIGHDPIPIXMAPS=1
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_X11_NO_MITSHM=1

if [ -f ./Glitch ] && [ -r ./Glitch ] && [ -x ./Glitch ]
then
    echo "Launching a local Glitch."
    set_qt_qpa_platformtheme "./Glitch"
    ./Glitch "$@"
    exit $?
fi

if [ -f /opt/glitch/Glitch ] && \
   [ -r /opt/glitch/Glitch ] && \
   [ -x /opt/glitch/Glitch ]
then
    echo "Launching an official Glitch (/opt/glitch)."
    set_qt_qpa_platformtheme "/opt/glitch/Glitch"
    /opt/glitch/Glitch "$@"
    exit $?
fi

if [ -f /usr/local/glitch/Glitch ] && \
   [ -r /usr/local/glitch/Glitch ] && \
   [ -x /usr/local/glitch/Glitch ]
then
    echo "Launching an official Glitch (/usr/local/glitch)."
    set_qt_qpa_platformtheme "/usr/local/glitch/Glitch"
    /usr/local/glitch/Glitch "$@"
    exit $?
fi

echo "Cannot locate Glitch. Why?"
exit 1
