/**
 * Copyright (c) 2014-present, The osquery authors
 *
 * This source code is licensed as defined by the LICENSE file found in the
 * root directory of this source tree.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR GPL-2.0-only)
 */

#include <iostream>

#include <osquery/config/config.h>
#include <osquery/registry/registry_factory.h>
#include <plugins/config/parsers/kafka_config.h>

namespace osquery {

/// Root key to retrieve Kafka pass-thru configurations.
const std::string kKafkaConfigParserRootKey("kafka_config");

std::vector<std::string> KafkaConfigConfigParserPlugin::keys() const {
  return {kKafkaConfigParserRootKey};
}

Status KafkaConfigConfigParserPlugin::update(const std::string& source,
                                             const ParserConfig& config) {
  auto settings = config.find(kKafkaConfigParserRootKey);
  if (settings != config.end()) {
    auto doc = JSON::newObject();
    auto obj = doc.getObject();
    doc.copyFrom(settings->second.doc(), obj);
    doc.add(kKafkaConfigParserRootKey, obj);
    data_ = std::move(doc);
  }
  return Status();
}

REGISTER_INTERNAL(KafkaConfigConfigParserPlugin,
                  "config_parser",
                  "kafka_config");
} // namespace osquery
