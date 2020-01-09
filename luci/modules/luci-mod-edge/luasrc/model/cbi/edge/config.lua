-- Copyright 2020 Simon Crawley <simon.crawley@gotosage.com>
-- Licensed to the public under the Apache License 2.0.

local m = Map("edge", translate("EDGE Configuration"), translate("Customize device-specific parameters used by the SAGE EDGE binaries"))
m.tabbed = true

general = m:section(TypedSection, "general", "General")
general.addremove = false
general.anonymous = true

general_logfile = general:option(Value, "log_file", "Log file location")
general_logfile.default = "/var/log/edge.log"
general_logfile.size = 32
general_logfile.optional = false
general_logfile.rmempty = false

general_datafile = general:option(Value, "data_file", "Data file location")
general_datafile.default = "/var/log/edge.data"
general_datafile.size = 32
general_datafile.optional = false
general_datafile.rmempty = false

general_verbose = general:option(ListValue, "verbose", "Debug output level")
general_verbose:value("0", "None")
general_verbose:value("1", "Level1")
general_verbose:value("2", "Level2")
general_verbose:value("3", "Level3")
general_verbose:value("4", "Level4")
general_verbose.default = "0"
general_verbose.optional = false
general_verbose.rmempty = false

general_lap = general:option(Flag, "enable_lap", "Enable LAP Scanning")
general_lap.default = "true"
general_lap.enabled = "true"
general_lap.disabled = "false"
general_lap.optional = false
general_lap.rmempty = false

general_hci = general:option(Flag, "enable_hci", "Enable HCI Scanning")
general_hci.default = "true"
general_hci.enabled = "true"
general_hci.disabled = "false"
general_hci.optional = false
general_hci.rmempty = false

general_hci_le = general:option(Flag, "enable_hci_le", "Enable HCI LE Scanning")
general_hci_le.default = "true"
general_hci_le.enabled = "true"
general_hci_le.disabled = "false"
general_hci_le.optional = false
general_hci_le.rmempty = false

general_wifi = general:option(Flag, "enable_wifi", "Enable WiFi Scanning")
general_wifi.default = "true"
general_wifi.enabled = "true"
general_wifi.disabled = "false"
general_wifi.optional = false
general_wifi.rmempty = false

collector = m:section(TypedSection, "collector", "Data Collector")
collector.addremove = false
collector.anonymous = true

collector_enabled = collector:option(Flag, "enabled", "Enable")
collector_enabled.default = "true"
collector_enabled.enabled = "true"
collector_enabled.disabled = "false"
collector_enabled.optional = false
collector_enabled.rmempty = false

collector_listen_ip = collector:option(Value, "listen_ip", "Listen IP", "IP Address to listen for scan results on")
collector_listen_ip.default = "127.0.0.1"
collector_listen_ip.size = 16
collector_listen_ip.optional = false
collector_listen_ip.rmempty = false

collector_listen_port = collector:option(Value, "listen_port", "Listen Port", "Port to listen for scan results on")
collector_listen_port.default = "2000"
collector_listen_port.size = 6
collector_listen_port.optional = false
collector_listen_port.rmempty = false

collector_server_ip = collector:option(Value, "server_ip", "Server IP", "IP Address to transmit scan results to")
collector_server_ip.default = "127.0.0.1"
collector_server_ip.size = 16
collector_server_ip.optional = false
collector_server_ip.rmempty = false

collector_server_port = collector:option(Value, "server_port", "Server Port", "Port to transmit scan results to")
collector_server_port.default = "2000"
collector_server_port.size = 6
collector_server_port.optional = false
collector_server_port.rmempty = false

addinsight = m:section(TypedSection, "addinsight", "Addinsight UDP")
addinsight.addremove = false
addinsight.anonymous = true

addinsight_enabled = addinsight:option(Flag, "enabled", "Enable")
addinsight_enabled.default = "true"
addinsight_enabled.enabled = "true"
addinsight_enabled.disabled = "false"
addinsight_enabled.optional = false
addinsight_enabled.rmempty = false

addinsight_site_id = addinsight:option(Value, "site_id", "Site ID", "Site ID to report to the specified Addinsight server")
addinsight_site_id.default = "9901"
addinsight_site_id.size = 5
addinsight_site_id.optional = false
addinsight_site_id.rmempty = false

addinsight_server_ip = addinsight:option(Value, "server_ip", "Server IP", "IP Address to transmit Addinsight UDP packets to")
addinsight_server_ip.default = "127.0.0.1"
addinsight_server_ip.size = 16
addinsight_server_ip.optional = false
addinsight_server_ip.rmempty = false

addinsight_server_port = addinsight:option(Value, "server_port", "Server Port", "Port to transmit Addinsight UDP packets to")
addinsight_server_port.default = "2000"
addinsight_server_port.size = 6
addinsight_server_port.optional = false
addinsight_server_port.rmempty = false

return m