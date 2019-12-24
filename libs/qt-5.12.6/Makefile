#
# Copyright (C) 2013 Riccardo Ferrazzo <f.riccardo87@gmail.com>
# Copyright (C) 2017 Paweł Knioła <pawel.kn@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_VERSION:=5.12
PKG_RELEASE:=6
PKG_NAME:=qt-$(PKG_VERSION).$(PKG_RELEASE)
PKG_MD5SUM:=287d71e71ebd97f77220873e7b131b1a

PKG_SOURCE:=qt-everywhere-src-$(PKG_VERSION).$(PKG_RELEASE).tar.xz
PKG_SOURCE_URL:=http://download.qt.io/archive/qt/$(PKG_VERSION)/$(PKG_VERSION).$(PKG_RELEASE)/single
PKG_BUILD_DIR=$(BUILD_DIR)/qt-everywhere-src-$(PKG_VERSION).$(PKG_RELEASE)
PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0
PKG_BUILD_DEPENDS:=libiconv

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk
#include $(TARGET_LDFLAGS)/nls.mk

#-include $(if $(DUMP),,./files/qmake.mk)

# not using sstrip here as this fucks up the .so's somehow
STRIP:=/bin/true
RSTRIP:= \
  NM="$(TOOLCHAIN_DIR)/bin/$(TARGET_CROSS)nm" \
  STRIP="$(STRIP)" \
  STRIP_KMOD="$(STRIP)" \
  $(SCRIPT_DIR)/rstrip.sh

define Package/$(PKG_NAME)/Default
  SECTION:=libs
  CATEGORY:=Libraries
  SUBMENU:=Qt5
  TITLE:=qt5
  URL:=http://qt-project.org
  DEPENDS:=+librt +zlib +libstdcpp +libpcre16 +libpthread +libatomic +libmysqlclient @!LINUX_2_6
endef

define Package/$(PKG_NAME)-core
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=core
endef

define Package/$(PKG_NAME)-concurrent
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=concurrent
  DEPENDS+=+$(PKG_NAME)-core
endef

define Package/$(PKG_NAME)-network
  $(call Package/qt-$(PKG_VERSION).$(PKG_RELEASE)/Default)
  TITLE+=network
  DEPENDS+=+$(PKG_NAME)-core
endef

define Package/$(PKG_NAME)-serialbus
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=serialbus
  DEPENDS+=+$(PKG_NAME)-core +$(PKG_NAME)-network +$(PKG_NAME)-serialport
endef

define Package/$(PKG_NAME)-serialport
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=serialport
  DEPENDS+=+$(PKG_NAME)-core
endef

define Package/$(PKG_NAME)-widgets
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=widgets
  DEPENDS+=+$(PKG_NAME)-core +$(PKG_NAME)-network
endef

define Package/$(PKG_NAME)-sql
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=sql
  DEPENDS+=+$(PKG_NAME)-core
endef

define Package/$(PKG_NAME)-xml
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=xml
  DEPENDS+=+$(PKG_NAME)-core
endef

define Package/$(PKG_NAME)-xmlpatterns
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=xmlpatterns
  DEPENDS+=+$(PKG_NAME)-core +$(PKG_NAME)-network
endef

define Package/$(PKG_NAME)-test
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=test
  DEPENDS+=+$(PKG_NAME)-core
endef

define Build/Configure
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/qtbase/lib/fonts
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/qtbase/mkspecs/linux-openwrt-g++
	$(CP) ./files/fonts/* $(PKG_BUILD_DIR)/qtbase/lib/fonts/
	$(CP) ./files/qplatformdefs.h $(PKG_BUILD_DIR)/qtbase/mkspecs/linux-openwrt-g++/qplatformdefs.h
	$(CP) ./files/qmake.conf $(PKG_BUILD_DIR)/qtbase/mkspecs/linux-openwrt-g++/qmake.conf
	$(SED) 's@$$$$(TARGET_CROSS)@$(TARGET_CROSS)@g' $(PKG_BUILD_DIR)/qtbase/mkspecs/linux-openwrt-g++/qmake.conf
	( cd $(PKG_BUILD_DIR) ; \
		TARGET_CC="$(TARGET_CROSS)gcc" \
		TARGET_CXX="$(TARGET_CROSS)g++" \
		TARGET_AR="$(TARGET_CROSS)ar cqs" \
		TARGET_OBJCOPY="$(TARGET_CROSS)objcopy" \
		TARGET_RANLIB="$(TARGET_CROSS)ranlib" \
		TARGET_CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
		TARGET_CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS) $(EXTRA_LDFLAGS) -lpthread -lrt" \
		TARGET_INCDIRS="$(TARGET_INCDIRS)" \
		TARGET_LIBDIRS="$(TARGET_LIBDIRS) $(STAGING_DIR)/usr/lib/" \
		CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS)" \
		CXXFLAGS= \
		LDFLAGS= \
		./configure \
			-prefix /usr \
			-extprefix $(TOOLCHAIN_DIR) \
			-sysroot $(TOOLCHAIN_DIR) \
			-plugindir /usr/lib/Qt/plugins \
			-xplatform linux-openwrt-g++ \
			-opensource \
			-confirm-license \
			-force-asserts \
			-no-iconv \
			-no-pch \
			-no-rpath \
			-no-strip \
			-no-cups \
			-no-dbus \
			-no-eglfs \
			-no-kms \
			-no-opengl \
			-no-directfb \
			-no-xcb \
			-no-ssl \
			-qt-zlib \
			-qt-freetype \
			-make libs \
			-nomake examples \
			-nomake tests \
			-skip qtdeclarative \
			-skip qtmultimedia \
			-skip activeqt \
			-skip qtdoc \
			-skip qtconnectivity \
			-skip wayland \
			-skip qtscript \
			-sql-mysql \
			-I$(STAGING_DIR)/usr/include/mysql \
			-L$(STAGING_DIR)/usr/lib \
			-v \
	)
endef

define Build/Compile
	TARGET_CC="$(TARGET_CROSS)gcc" \
	TARGET_CXX="$(TARGET_CROSS)g++" \
	TARGET_AR="$(TARGET_CROSS)ar cqs" \
	TARGET_OBJCOPY="$(TARGET_CROSS)objcopy" \
	TARGET_RANLIB="$(TARGET_CROSS)ranlib" \
	TARGET_CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	TARGET_CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	TARGET_LDFLAGS="$(TARGET_LDFLAGS) $(EXTRA_LDFLAGS) -ldl -lpthread -lrt" \
	TARGET_INCDIRS="$(TARGET_INCDIRS)" \
	TARGET_LIBDIRS="$(TARGET_LIBDIRS) $(STAGING_DIR)/usr/lib/" \
	STAGING_DIR="$(STAGING_DIR)" \
	STAGING_DIR_HOST="$(STAGING_DIR)/../host" \
	PKG_CONFIG_SYSROOT="$(STAGING_DIR)" \
	TARGET_CPPFLAGS+="-I$(STAGING_DIR)/usr/include/mysql" \
	TARGET_LDFLAGS+="-L$(STAGING_DIR)/usr/lib/mysql -lmysqlclient" \
	CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS)" \
	$(MAKE) -j4 -C $(PKG_BUILD_DIR)
endef

define Build/InstallDev
	$(MAKE) -C $(PKG_BUILD_DIR) install
	$(CP) $(PKG_BUILD_DIR)/qtbase/bin/qmake $(TOOLCHAIN_DIR)/bin/
	$(CP) $(PKG_BUILD_DIR)/qtbase/bin/qt.conf $(TOOLCHAIN_DIR)/bin/
endef

define Package/$(PKG_NAME)-core/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Core.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Core.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Core.la $(1)/usr/lib/
endef

define Package/$(PKG_NAME)-concurrent/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Concurrent.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Concurrent.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Concurrent.la $(1)/usr/lib/
endef

define Package/$(PKG_NAME)-network/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Network.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Network.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Network.la $(1)/usr/lib/
endef

define Package/$(PKG_NAME)-serialport/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtserialport/lib/libQt5SerialPort.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtserialport/lib/libQt5SerialPort.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtserialport/lib/libQt5SerialPort.la $(1)/usr/lib/
endef

define Package/$(PKG_NAME)-serialbus/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtserialbus/lib/libQt5SerialBus.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtserialbus/lib/libQt5SerialBus.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtserialbus/lib/libQt5SerialBus.la $(1)/usr/lib/
endef

define Package/$(PKG_NAME)-widgets/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/Qt/plugins/generic/
	$(INSTALL_DIR) $(1)/usr/lib/Qt/plugins/platforms/
	$(INSTALL_DIR) $(1)/usr/lib/Qt/plugins/imageformats/
	$(INSTALL_DIR) $(1)/usr/lib/fonts/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Gui.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Gui.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Gui.la 	$(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtsvg/lib/libQt5Svg.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtsvg/lib/libQt5Svg.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtsvg/lib/libQt5Svg.la $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Widgets.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Widgets.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Widgets.la $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/plugins/generic/*.so $(1)/usr/lib/Qt/plugins/generic/
	$(CP) $(PKG_BUILD_DIR)/qtbase/plugins/platforms/*.so $(1)/usr/lib/Qt/plugins/platforms/
	$(CP) $(PKG_BUILD_DIR)/qtbase/plugins/imageformats/*.so $(1)/usr/lib/Qt/plugins/imageformats/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/fonts/* $(1)/usr/lib/fonts/
endef

define Package/$(PKG_NAME)-sql/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/Qt/plugins/sqldrivers/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Sql.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Sql.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Sql.la 	$(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/plugins/sqldrivers/*.so $(1)/usr/lib/Qt/plugins/sqldrivers/
endef

define Package/$(PKG_NAME)-xml/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Xml.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Xml.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Xml.la 	$(1)/usr/lib/
endef

define Package/$(PKG_NAME)-xmlpatterns/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtxmlpatterns/lib/libQt5XmlPatterns.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtxmlpatterns/lib/libQt5XmlPatterns.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtxmlpatterns/lib/libQt5XmlPatterns.la $(1)/usr/lib/
endef

define Package/$(PKG_NAME)-test/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Test.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Test.prl $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/qtbase/lib/libQt5Test.la $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)-core))
$(eval $(call BuildPackage,$(PKG_NAME)-concurrent))
$(eval $(call BuildPackage,$(PKG_NAME)-network))
$(eval $(call BuildPackage,$(PKG_NAME)-serialport))
$(eval $(call BuildPackage,$(PKG_NAME)-serialbus))
$(eval $(call BuildPackage,$(PKG_NAME)-widgets))
$(eval $(call BuildPackage,$(PKG_NAME)-sql))
$(eval $(call BuildPackage,$(PKG_NAME)-xml))
$(eval $(call BuildPackage,$(PKG_NAME)-xmlpatterns))
$(eval $(call BuildPackage,$(PKG_NAME)-test))
