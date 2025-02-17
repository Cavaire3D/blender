/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright 2022 Blender Foundation. All rights reserved. */

/** \file
 * \ingroup gpu
 */

#pragma once

#include "gpu_backend.hh"

namespace blender::gpu {

class VKBackend : public GPUBackend {
 public:
  VKBackend()
  {
    VKBackend::init_platform();
  }

  virtual ~VKBackend()
  {
    VKBackend::platform_exit();
  }

  void delete_resources() override;

  void samplers_update() override;
  void compute_dispatch(int groups_x_len, int groups_y_len, int groups_z_len) override;
  void compute_dispatch_indirect(StorageBuf *indirect_buf) override;

  Context *context_alloc(void *ghost_window, void *ghost_context) override;

  Batch *batch_alloc() override;
  DrawList *drawlist_alloc(int list_length) override;
  FrameBuffer *framebuffer_alloc(const char *name) override;
  IndexBuf *indexbuf_alloc() override;
  QueryPool *querypool_alloc() override;
  Shader *shader_alloc(const char *name) override;
  Texture *texture_alloc(const char *name) override;
  UniformBuf *uniformbuf_alloc(int size, const char *name) override;
  StorageBuf *storagebuf_alloc(int size, GPUUsageType usage, const char *name) override;
  VertBuf *vertbuf_alloc() override;

  /* Render Frame Coordination --
   * Used for performing per-frame actions globally */
  void render_begin() override;
  void render_end() override;
  void render_step() override;

 private:
  static void init_platform();
  static void platform_exit();
};

}  // namespace blender::gpu