include $(TOPDIR)/rules.mk

PKG_NAME:=libbtbb
PKG_VERSION:=2018-12-R1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://github.com/greatscottgadgets/libbtbb/archive/
PKG_HASH:=6f15b812c2bbdb7ebbfc4e6317769cf84a6feb3c316bf3fd668f927b4bcf2901

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
	SECTION:=libs
	CATEGORY:=Libraries
	DEPENDS:=+glib2
	TITLE:=Bluetooth baseband decoding library
endef

define Package/$(PKG_NAME)/description
	This is the Bluetooth baseband decoding library, forked from the GR-Bluetooth project. 
	It can be used to extract Bluetooth packet and piconet information from Ubertooth devices 
	as well as GR-Bluetooth/USRP.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(DL_DIR)/* $(PKG_BUILD_DIR)/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libbtbb.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

