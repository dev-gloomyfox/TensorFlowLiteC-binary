/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef TENSORFLOW_COMPILER_XLA_SERVICE_DYNAMIC_DIMENSION_SIMPLIFIER_H_
#define TENSORFLOW_COMPILER_XLA_SERVICE_DYNAMIC_DIMENSION_SIMPLIFIER_H_

#include <utility>

#include "tensorflow/compiler/xla/service/hlo_module.h"
#include "tensorflow/compiler/xla/service/hlo_pass_interface.h"

namespace xla {

// This pass simplifies operations on dynamic dimension sizes so that it can be
// easily analyzed by later passes.
class DynamicDimensionSimplifier : public HloModulePass {
 public:
  absl::string_view name() const override {
    return "dynamic dimension simplifier";
  }

  StatusOr<bool> Run(HloModule* module) override;
};
}  // namespace xla

#endif  // TENSORFLOW_COMPILER_XLA_SERVICE_DYNAMIC_DIMENSION_SIMPLIFIER_H_
