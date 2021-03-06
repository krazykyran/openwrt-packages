include $(TOPDIR)/rules.mk

PKG_NAME:=libbtbb
PKG_VERSION:=2018-12-R1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/greatscottgadgets/libbtbb.git
PKG_SOURCE_VERSION:=2018-12-R1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libbtbb
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=Bluetooth baseband decoding library
endef

define Package/libbtbb/description
	This is the Bluetooth baseband decoding library, forked from the GR-Bluetooth project. 
	It can be used to extract Bluetooth packet and piconet information from Ubertooth devices 
	as well as GR-Bluetooth/USRP.
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libbtbb.so.1.0 $(1)/usr/lib/
	$(LN) libbtbb.so.1.0 $(1)/usr/lib/libbtbb.so.1
	$(LN) libbtbb.so.1 $(1)/usr/lib/libbtbb.so
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libbtbb.pc $(1)/usr/lib/pkgconfig/
endef

define Package/libbtbb/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libbtbb.so.1.0 $(1)/usr/lib/
	$(LN) libbtbb.so.1.0 $(1)/usr/lib/libbtbb.so.1
	$(LN) libbtbb.so.1.0 $(1)/usr/lib/libbtbb.so
endef

$(eval $(call BuildPackage,libbtbb))

