rm -rf "app"
rm server

wget https://github.com/project-papa/project-papa-server/releases/download/0.0.1/server
chmod +x ./server

wget http://sonic-pi.net/files/releases/v2.11.1/Sonic-Pi-for-Mac-v2.11.1.dmg

hdiutil mount Sonic-Pi-for-Mac-v2.11.1.dmg
cp -R "/Volumes/Sonic Pi v2.11.1/Sonic Pi.app" ./app

hdiutil unmount "/Volumes/Sonic Pi v2.11.1"
rm Sonic-Pi-for-Mac-v2.11.1.dmg
