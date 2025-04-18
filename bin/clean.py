#!/usr/bin/env python3

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import shutil


def delete_files_and_directories(paths):
    for path in paths:
        if os.path.exists(path):
            if os.path.isfile(path):
                try:
                    os.remove(path)
                    print(f"Deleted file: {path}")
                except Exception as e:
                    print(f"Error deleting file {path}: {e}")
            elif os.path.isdir(path):
                try:
                    shutil.rmtree(path)
                    print(f"Deleted directory: {path}")
                except Exception as e:
                    print(f"Error deleting directory {path}: {e}")
            else:
                print(f"Invalid path: {path}")


paths_to_delete = [
    "Plugins/RuleRanger/Binaries",
    "Plugins/RuleRanger/Intermediate",
    "Plugins/MDMetaDataEditor/Binaries",
    "Plugins/MDMetaDataEditor/Intermediate",
    "DerivedDataCache",
    "Binaries",
    "Intermediate",
    "Saved",
    "cmake-build-debug"
]

delete_files_and_directories(paths_to_delete)
