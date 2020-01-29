include $(TOPDIR)/rules.mk

PKG_NAME:=ubertooth
PKG_VERSION:=2018-12-R1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/greatscottgadgets/ubertooth.git
PKG_SOURCE_VERSION:=0adf33ee73a5ae9ee713948d19c1743fdf0e9a03
PKG_BUILD_DEPENDS:=libbtbb

CMAKE_BINARY_SUBDIR:=host
CMAKE_SOURCE_SUBDIR:=host

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Utilities
	DEPENDS:=+libbtbb +libusb-1.0 +bluez-libs
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
