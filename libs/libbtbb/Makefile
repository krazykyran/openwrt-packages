include $(TOPDIR)/rules.mk

PKG_NAME:=libbtbb
PKG_VERSION:=2018-12-R1

PKG_SOURCE:=$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://github.com/greatscottgadgets/libbtbb/archive
PKG_SOURCE_VERSION:=2018-12-R1
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_HASH:=3e93a2b325f982dc585f734542bce4bc734f57f9a07066b47d96bed848f83327

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=Bluetooth baseband decoding library
endef

define Package/$(PKG_NAME)/description
	This is the Bluetooth baseband decoding library, forked from the GR-Bluetooth project. 
	It can be used to extract Bluetooth packet and piconet information from Ubertooth devices 
	as well as GR-Bluetooth/USRP.
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/btaptap $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libbtbb.so.1.0 $(1)/usr/lib/
	$(LN) ./libbtbb.so.1.0 $(1)/usr/lib/libbtbb.so.1
	$(LN) ./libbtbb.so.1.0 $(1)/usr/lib/libbtbb.so
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libbtbb.pc $(1)/usr/lib/pkgconfig/
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

$(eval $(call BuildPackage,$(PKG_NAME)))

