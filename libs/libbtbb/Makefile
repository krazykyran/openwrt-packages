include $(TOPDIR)/rules.mk

PKG_NAME:=libbtbb
PKG_VERSION:=2018-12-R1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://github.com/greatscottgadgets/libbtbb/archive/
PKG_HASH:=3e93a2b325f982dc585f734542bce4bc734f57f9a07066b47d96bed848f83327

include $(INCLUDE_DIR)/package.mk

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

$(eval $(call BuildPackage,$(PKG_NAME)))

