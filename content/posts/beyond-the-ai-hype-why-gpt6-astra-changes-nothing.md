---
author: "Marco Carletti"
title: "Beyond the Hype: why GPT-6 Astra changes nothing"
date: 2026-09-07T10:49:50+02:00
draft: false
tags: ["artificial intelligence", "llm", "gpt"]
---

<center><img src="/assets/comet.jpg" style="padding: 2rem; height: 360px;"/></center>

OpenAI recently released the GPT-6 Astra model. My controversial opinion is that I see no difference compared to the past. Let me explain.

Everything we see is marketing. It's a new chassis on the same engine. All GPT models, whether from OpenAI, Anthropic, or Google, are built on the same underlying Transformer architecture. This also applies to multimodal models, which intelligently integrate components like image tokenizers.

I’ll push my controversial take even further: GPT-like models excel at generating UI code, simple games, and basic 3D assets in seconds. But what else? You still have to tweak the output to produce a production-ready product. AI is more than enough to launch a state-of-the-art landing page, a UI mockup, or a basic demo for a game mechanic. But to take it to production, you still need to know how the "engine burns its fuel."

Consider an example: ask any AI model to calibrate a multi-camera system with a sub-pixel reprojection error. It might manage reasonably well because that task is sufficiently documented. Now push further: ask the model to generate a face detector that estimates 2D bounding boxes from an image. Seems easy? Now add real-world constraints: optimize that model for production, cap it at 1 million parameters (roughly 1 MB of memory), limit inference time to under 20 ms on a 320x240 image, and deploy it using TensorRT on a Raspberry Pi 5.

Given enough time and data, a GPT model might eventually reach a reasonable solution. Data has always been the bottleneck in AI. But here is my point: **where data is limited and noisy, no AI will surpass a human expert.** Where outputs must satisfy strict design constraints and hardware boundaries, AI can accelerate drafting, but the last mile remains a matter of human experience and intuition.

That is why we must stay sharp, keep learning, and embrace technological progress. For junior developers, building foundational intuition through hands-on problem-solving is essential before delegating to coding agents. Senior developers must likewise keep their cognitive muscles active.

Let’s embrace the change and enjoy it, but never assume we no longer need calculus just because someone invented the calculator.