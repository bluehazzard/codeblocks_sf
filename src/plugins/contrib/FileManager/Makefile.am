AM_CPPFLAGS = $(WX_CXXFLAGS) \
		$(CB_GAMIN_CFLAGS) \
		-I$(top_srcdir)/src/include \
		-I$(top_srcdir)/src/sdk/wxscintilla/include \
		-I$(top_srcdir)/src/include/mozilla_chardet \
		-I$(top_srcdir)/src/include/mozilla_chardet/mfbt \
		-I$(top_srcdir)/src/include/mozilla_chardet/nsprpub/pr/include \
		-I$(top_srcdir)/src/include/mozilla_chardet/xpcom \
		-I$(top_srcdir)/src/include/mozilla_chardet/xpcom/base \
		-I$(top_srcdir)/src/include/mozilla_chardet/xpcom/glue \
		-D__FAM__

pluginlibdir = $(pkglibdir)/plugins

pluginlib_LTLIBRARIES = libFileManager.la

libFileManager_la_LDFLAGS = @MODULE_SHARED_LDFLAGS@ -version-info 0:1:0 -no-undefined -avoid-version

libFileManager_la_LIBADD = ../../../sdk/libcodeblocks.la $(WX_LIBS) $(CB_GAMIN_LIBS)

libFileManager_la_SOURCES = FileManager.cpp \
			FileExplorer.cpp \
			FileExplorerSettings.cpp \
			FileExplorerUpdater.cpp \
			CommitBrowser.cpp \
			directorymonitor.cpp \
			se_globals.cpp

noinst_HEADERS =  	FileManager.h \
			FileExplorer.h \
			FileExplorerSettings.h \
			FileExplorerUpdater.h \
			CommitBrowser.h \
			directorymonitor.h \
			se_globals.h

EXTRA_DIST = 	$(srcdir)/*.cbp \
		$(srcdir)/Resources/fileexplorersettings.xrc \
		$(srcdir)/Resources/CommitBrowser.xrc \
		$(srcdir)/manifest.xml

pkgdata_DATA = FileManager.zip
CLEANFILES = $(pkgdata_DATA)

FileManager.zip: manifest.xml Resources/fileexplorersettings.xrc Resources/CommitBrowser.xrc
	PWD=`pwd` cd $(srcdir) && zip -j9 $(PWD)/FileManager.zip manifest.xml Resources/fileexplorersettings.xrc Resources/CommitBrowser.xrc > /dev/null
