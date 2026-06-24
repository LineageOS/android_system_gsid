/*
 * Copyright (C) 2026 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include <string>
#include <android/gsi/IGsiService.h>

#include "../gsi_service.h"

using android::gsi::IGsiService;

namespace android {
namespace gsi {

class GsiServiceTest : public ::testing::Test {
  protected:
    void SetUp() override {}
    void TearDown() override {}

    static int ValidateInstallParams(std::string& install_dir) {
        return GsiService::ValidateInstallParams(install_dir);
    }
};

TEST_F(GsiServiceTest, ValidateInstallParams_ValidLayout) {
    std::string path = "/data/gsi/dsu/dsu_slot";
    EXPECT_EQ(ValidateInstallParams(path), IGsiService::INSTALL_OK);
    EXPECT_EQ(path, "/data/gsi/dsu/dsu_slot/");
}

TEST_F(GsiServiceTest, ValidateInstallParams_ValidLockedLayout) {
    std::string path = "/data/gsi/dsu/foo.lock";
    EXPECT_EQ(ValidateInstallParams(path), IGsiService::INSTALL_OK);
    EXPECT_EQ(path, "/data/gsi/dsu/foo.lock/");
}

TEST_F(GsiServiceTest, ValidateInstallParams_RejectsMultiComponentSlot) {
    std::string path = "/data/gsi/dsu/A/B.lock";
    EXPECT_NE(ValidateInstallParams(path), IGsiService::INSTALL_OK);
}

TEST_F(GsiServiceTest, ValidateInstallParams_RejectsPathOutsideDsuFolder) {
    std::string path = "/data/gsi/foo/bar";
    EXPECT_NE(ValidateInstallParams(path), IGsiService::INSTALL_OK);
}

TEST_F(GsiServiceTest, ValidateInstallParams_RejectsReservedSlot) {
    std::string path = "/data/gsi/dsu/booted";
    EXPECT_NE(ValidateInstallParams(path), IGsiService::INSTALL_OK);
}

} // namespace gsi
} // namespace android
