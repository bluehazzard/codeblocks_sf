EXTRA_DIST = manifest.xml new_class.xrc configuration.xrc

pkgdata_DATA = classwizard.zip
CLEANFILES = $(pkgdata_DATA)

classwizard.zip: $(EXTRA_DIST)
	PWD=`pwd` cd $(srcdir) && zip $(PWD)/classwizard.zip manifest.xml *.xrc > /dev/null
