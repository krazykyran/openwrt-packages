include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=linux-headers
PKG_VERSION:=$(LINUX_VERSION)-$(LINUX_RELEASE)
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=devel
  CATEGORY:=Development
  TITLE:=linux-headers (Development headers)
  DEPENDS:=+libncurses-dev +make +gcc +pkg-config +ldconfig +bc +kmod-ikconfig
  URL:=http://www.kernel.org/
endef

define Package/$(PKG_NAME)/description
  linux-headers files for development
endef

# Prepare, Configure, Compile already done by kernel depends
define Build/Prepare
	
endef

define Build/Configure
	
endef

define Build/Compile
	
endef

# Determine gcc version
GCC_VERSION:=$(call qstrip,$(CONFIG_GCC_VERSION))
# Same version as in feeds/packages/devel/gcc/Makefile
GCC_VER:=7.3.0

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/src/linux-$(LINUX_VERSION)
	$(INSTALL_DIR) $(1)/lib/modules/$(LINUX_VERSION)
	cp $(LINUX_DIR)/.config $(1)/usr/src/linux-$(LINUX_VERSION)
	$(CP) $(LINUX_DIR)/* $(1)/usr/src/linux-$(LINUX_VERSION)
	$(LN) /usr/src/linux-$(LINUX_VERSION) $(1)/lib/modules/$(LINUX_VERSION)/build
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
