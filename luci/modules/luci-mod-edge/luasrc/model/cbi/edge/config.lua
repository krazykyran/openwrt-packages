-- Copyright 2020 Simon Crawley <simon.crawley@gotosage.com>
-- Licensed to the public under the Apache License 2.0.

m = Map("edge", translate("EDGE Configuration"), translate("Customize device-specific parameters used by the SAGE EDGE binaries"))

general = m:section(TypedSection, "general", "General Settings")
general.addremove = false

general_logfile = general:option(Value, "log_file", "Log file location")
general_logfile.default = "/var/log/edge.log"
general_logfile.optional = false
general_logfile.rmempty = false
general_logfile.size = 32

general_datafile = general:option(Value, "data_file", "Data file location")
general_datafile.default = "/var/log/edge.data"
general_datafile.optional = false
general_datafile.rmempty = false
general_datafile.size = 32

general_verbose = general:option(ListValue, "verbose", "Debug output level")
general_verbose:value("0", "None")
general_verbose:value("1", "Level1")
general_verbose:value("2", "Level2")
general_verbose:value("3", "Level3")
general_verbose:value("4", "Level4")
general_verbose.default = "0"
general_verbose.optional = false
general_verbose.rmempty = false

return m