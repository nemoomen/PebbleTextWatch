c:
	./waf configure && ./waf build
l: c
	../libpebble/p.py --pebble_id 00:18:2F:CC:3C:9F --lightblue load ./build/BgTextWatch.pbw
d: c
	../libpebble/p.py --pebble_id 00:18:2F:CC:3C:9F --lightblue reinstall ./build/BgTextWatch.pbw 
