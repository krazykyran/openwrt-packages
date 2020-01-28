include $(TOPDIR)/rules.mk

PKG_NAME:=ubertooth
PKG_VERSION:=2018-12-R1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://github.com/greatscottgadgets/ubertooth/archive/
PKG_HASH:=6f15b812c2bbdb7ebbfc4e6317769cf84a6feb3c316bf3fd668f927b4bcf2901
PKG_BUILD_DEPENDS:=libbtbb-dev libusb-1.0-0-dev libbluetooth-dev

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Utilities
	DEPENDS:=+libbtbb +libusb-1.0
	TITLE:=Project Ubertooth
endef

define Package/$(PKG_NAME)/description
	Project Ubertooth is an open source wireless development platform suitable
	for Bluetooth experimentation. Ubertooth ships with a capable BLE (Bluetooth Smart)
	sniffer and can sniff some data from Basic Rate (BR) Bluetooth Classic connections.
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

