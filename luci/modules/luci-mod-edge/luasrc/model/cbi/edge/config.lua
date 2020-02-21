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

addinsight_server_ip = addinsight:option(Value, "server_ip", "Server Address", "Address to transmit Addinsight UDP packets to")
addinsight_server_ip.default = "127.0.0.1"
addinsight_server_ip.size = 16
addinsight_server_ip.optional = false
addinsight_server_ip.rmempty = false

addinsight_server_port = addinsight:option(Value, "server_port", "Server Port", "Port to transmit Addinsight UDP packets to")
addinsight_server_port.default = "2000"
addinsight_server_port.size = 6
addinsight_server_port.optional = false
addinsight_server_port.rmempty = false

addinsight_log_enabled = addinsight:option(Flag, "log_enabled", "Enable Logging")
addinsight_log_enabled.default = "false"
addinsight_log_enabled.enabled = "true"
addinsight_log_enabled.disabled = "false"
addinsight_log_enabled.optional = false
addinsight_log_enabled.rmempty = false

qtdf = m:section(TypedSection, "qtdf", "QLD TMR Data Format")
qtdf.addremove = false
qtdf.anonymous = true

qtdf_enabled = qtdf:option(Flag, "enabled", "Enable")
qtdf_enabled.default = "false"
qtdf_enabled.enabled = "true"
qtdf_enabled.disabled = "false"
qtdf_enabled.optional = false
qtdf_enabled.rmempty = false

qtdf_log_enabled = qtdf:option(Flag, "log_enabled", "Enable Logging")
qtdf_log_enabled.default = "false"
qtdf_log_enabled.enabled = "true"
qtdf_log_enabled.disabled = "false"
qtdf_log_enabled.optional = false
qtdf_log_enabled.rmempty = false

qtdf_log_path = qtdf:option(Value, "log_path", "Log file directory")
qtdf_log_path.default = "/home/data"
qtdf_log_path.size = 32
qtdf_log_path.optional = false
qtdf_log_path.rmempty = false

qtdf_device_id = qtdf:option(Value, "device_id", "Device ID", "Device ID to report to the specified Kafka server")
qtdf_device_id.default = "1234"
qtdf_device_id.size = 5
qtdf_device_id.optional = false
qtdf_device_id.rmempty = false

qtdf_device_desc = qtdf:option(Value, "device_desc", "Device Description", "Device description to report to the specified Kafka server")
qtdf_device_desc.default = "DeviceDescription"
qtdf_device_desc.size = 32
qtdf_device_desc.optional = false
qtdf_device_desc.rmempty = false

qtdf_kafka_server_ip = qtdf:option(Value, "kafka_server_ip", "Kafka Server Address", "Address to transmit Kafka packets to")
qtdf_kafka_server_ip.default = "172.20.0.2"
qtdf_kafka_server_ip.size = 16
qtdf_kafka_server_ip.optional = false
qtdf_kafka_server_ip.rmempty = false


qtdf_kafka_server_port = qtdf:option(Value, "kafka_server_port", "Kafka Server Port", "Port to transmit Kafka packets to")
qtdf_kafka_server_port.default = "9092"
qtdf_kafka_server_port.size = 6
qtdf_kafka_server_port.optional = false
qtdf_kafka_server_port.rmempty = false

qtdf_kafka_topic = qtdf:option(Value, "kafka_topic", "Kafka Topic", "Kafka Topic to deliver QTDF messages to")
qtdf_kafka_topic.default = "test_omnia"
qtdf_kafka_topic.size = 32
qtdf_kafka_topic.optional = false
qtdf_kafka_topic.rmempty = false

qtdf_kafka_publish_period = qtdf:option(Value, "kafka_publish_period_ms", "Kafka Publish Period (in ms)", "Time to wait (in ms) between transmitting QTDF frames to the specified Kafka server")
qtdf_kafka_publish_period.default = "5000"
qtdf_kafka_publish_period.size = 6
qtdf_kafka_publish_period.optional = false
qtdf_kafka_publish_period.rmempty = false

qtdf_flush_period_minutes = qtdf:option(Value, "flush_period_minutes", "Flush period (in minutes)", "Data is logged to file at the specified interval")
qtdf_flush_period_minutes.default = "60"
qtdf_flush_period_minutes.size = 6
qtdf_flush_period_minutes.optional = false
qtdf_flush_period_minutes.rmempty = false

qtdf_rollover_period_minutes = qtdf:option(Value, "rollover_period_minutes", "Rollover period (in minutes)", "Data is consolidated to a single file at the specified interval and a new log file is created")
qtdf_rollover_period_minutes.default = "1440"
qtdf_rollover_period_minutes.size = 6
qtdf_rollover_period_minutes.optional = false
qtdf_rollover_period_minutes.rmempty = false

qtdf_gps_datum = qtdf:option(Value, "gps_datum", "GPS Datum", "Geodetic datum to use with the provided latitude and longitude values")
qtdf_gps_datum.default = "GDA94"
qtdf_gps_datum.size = 16
qtdf_gps_datum.optional = false
qtdf_gps_datum.rmempty = false

qtdf_gps_latitude = qtdf:option(Value, "gps_latitude", "GPS Latitude")
qtdf_gps_latitude.default = "-27.472684"
qtdf_gps_latitude.size = 16
qtdf_gps_latitude.optional = false
qtdf_gps_latitude.rmempty = false

qtdf_gps_longitude = qtdf:option(Value, "gps_longitude", "GPS Longitude")
qtdf_gps_longitude.default = "153.028197"
qtdf_gps_longitude.size = 16
qtdf_gps_longitude.optional = false
qtdf_gps_longitude.rmempty = false

return m