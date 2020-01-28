'use strict';
'require rpc';
'require form';
'require network';

var callFileExec = rpc.declare({
	object: 'file',
	method: 'exec',
	params: [ '/usr/bin/mmcli', '-m 0' ],
	filter: function(value) {
		var res = value.substring(value.indexOf("/sys/devices/"));
		return res.slice(0, res.indexOf(" "));
	}
});

network.registerPatternVirtual(/^mobiledata-.+$/);
network.registerErrorCode('CALL_FAILED', _('Call failed'));
network.registerErrorCode('NO_CID',      _('Unable to obtain client ID'));
network.registerErrorCode('PLMN_FAILED', _('Setting PLMN failed'));

return network.registerProtocol('modemmanager', {
	getI18n: function() {
		return _('ModemManager');
	},

	getIfname: function() {
		return this._ubus('l3_device') || 'modemmanager-%s'.format(this.sid);
	},

	getOpkgPackage: function() {
		return 'modemmanager';
	},

	isFloating: function() {
		return true;
	},

	isVirtual: function() {
		return true;
	},

	getDevices: function() {
		return null;
	},

	containsDevice: function(ifname) {
		return (network.getIfnameOf(ifname) == this.getIfname());
	},

	renderFormOptions: function(s) {
		var dev = this.getL3Device() || this.getDevice(), o;
		
		o = s.taboption('general', form.ListValue, 'device', _('Modem device'));
		o.rmempty = false;
		o.load = function(section_id) {
			return callFileExec().then(L.bind(function(devices) {
				for (var i = 0; i < devices.length; i++)
					this.value(devices[i]);
				return form.Value.prototype.load.apply(this, [section_id]);
			}, this));
		};

		s.taboption('general', form.Value, 'apn', _('APN'));
		s.taboption('general', form.Value, 'pincode', _('PIN'));

		o = s.taboption('general', form.ListValue, 'auth', _('Authentication Type'));
		o.value('both', _('PAP/CHAP (both)'));
		o.value('pap', 'PAP');
		o.value('chap', 'CHAP');
		o.value('none', _('None'));
		o.default = 'none';

		o = s.taboption('general', form.Value, 'username', _('PAP/CHAP username'));
		o.depends('auth', 'pap');
		o.depends('auth', 'chap');
		o.depends('auth', 'both');

		o = s.taboption('general', form.Value, 'password', _('PAP/CHAP password'));
		o.depends('auth', 'pap');
		o.depends('auth', 'chap');
		o.depends('auth', 'both');
		o.password = true;

		o = s.taboption('general', form.ListValue, 'iptype', _('IP Type'));
		o.value('ipv4v6', _('IPv4/IPv6 (both - defaults to IPv4)'))
		o.value('ipv4', _('IPv4 only'));
		o.value('ipv6', _('IPv6 only'));
		o.default = 'ipv4v6';

		o = s.taboption('advanced', form.Value, 'mtu', _('Override MTU'));
		o.placeholder = dev ? (dev.getMTU() || '1500') : '1500';
		o.datatype    = 'max(9200)';
		
		s.taboption('general', form.Value, 'metric', _('Gateway metric'));

	}
});