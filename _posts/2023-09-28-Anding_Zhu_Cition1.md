---
title: A GaN MMIC Load-Modulated Balanced Amplifier With Modified Output Coupler for Efficiency Enhancement Over a Larger Power Back-Off Range
author: WaveDragon
date: 2023-11-14 11:11:00 +0800
categories: [Blogging, RadioFrequency]
tags: [Study]
math: true
mermaid: true
password_protect: false
# image:
#   path: /commons/devices-mockup.png
#   width: 800
#   height: 500
#   alt: Responsive rendering of Chirpy theme on multiple devices.
---

# 具有改进的输出耦合器的 GaN MMIC 负载调制平衡放大器，可在更大的功率回退范围内提高效率

## 摘要

本文首先介绍了一种采用 0.15um GaN 工艺开发的单片微波集成电路 (MMIC) 负载调制平衡放大器 (LMBA)。 在此简介中，非对称输出耦合器用于在更大的 OBO 范围内进一步增强输出功率和输出回退 (OBO) 效率。 这种MMIC LMBA工作模式依赖于三路有源负载调制过程，通过修改输出耦合器的耦合系数，可以提供更多的设计参数和自由度。 
为了在毫米波 (mm-wave) 下验证所提出的 LMBA，演示、制造并测试了 24.7-25.7 GHz MMIC LMBA。 测量结果表明，该 MMIC LMBA 可以提供 35.2dBm 的饱和输出功率，峰值漏极效率为 37.7%。 在 6dB/8dB/10dB OBO 下，可分别获得 23.8-30%、24.2-27% 和 20-24% 的功率附加效率 (PAE)。 测得的 S21 为 15 dB，增益变化为 ±0.4 dB。 当由 PAPR 为 9.2dB 的 100MHz 64-QAM OFDM 调制信号驱动时，通过 DPD 测量的 ACPR 提高至 –45.04 dBc。 在这种情况下，PA 的平均效率为 25.2%，平均输出功率为 26.2dBm。

## 介绍

大频谱资源可用性的无线需求导致微米波（mm-wave）频段在第五代（5G）无线通信中受到广泛的关注[^1]。 同时，具有高峰均功率比（PAPR）的调制信号得到普及，以实现最大频谱效率[^2]。 因此，考虑到PA在射频系统中的主导地位，需要在大输出功率回退（OBO）范围内具有高效率[^3]。













## 参考文献

[^1]: G. R. Nikandish, R. B. Staszewski, and A. Zhu, “Unbalanced power amplifier: An architecture for broadband back-off efficiency enhancement,” IEEE J. Solid-State Circuits, vol. 56, no. 2, pp. 367–381, Feb. 2021. 

[^2]: M. Bao, D. Gustafsson, R. Hou, Z. Ouarch, C. Chang, and K. Andersson, “A 24–28-GHz Doherty power amplifier with 4-W output power and 32% PAE at 6-dB OPBO in 150-nm GaN technology,” IEEE Microw. Wireless Compon. Lett., vol. 31, no. 6, pp. 752–755, Jun. 2021. 

[^3]: R.-J. Liu et al., “A 24–28-GHz GaN MMIC synchronous Doherty power amplifier with enhanced load modulation for 5G mm-Wave applications,” IEEE Trans. Microw. Theory Techn., vol. 70, no. 8, pp. 3910–3922, Aug. 2022. [^4]: D. P. Nguyen, J. Curtis, and A.-V. Pham, “A Doherty amplifier with modified load modulation scheme based on load-pull data,” IEEE Trans. Microw. Theory Techn., vol. 66, no. 1, pp. 227–236, Jan. 2018. 
[^5]: R. Giofre, A. D. Gaudio, W. Ciccognani, S. Colangeli, and E. Limiti, “A GaN-on-Si MMIC Doherty power amplifier for 5G applications,” in Proc. Asia–Pacific Microw. Conf. (APMC), Nov. 2018, pp. 971–973. 
[^6]: J. Xia, W. Chen, F. Meng, C. Yu, and X. Zhu, “Improved threestage Doherty amplifier design with impedance compensation in load combiner for broadband applications,” IEEE Trans. Microw. Theory Techn., vol. 67, no. 2, pp. 778–786, Feb. 2019. 
[^7]: Y. Xu, J. Pang, X. Wang, and A. Zhu, “Three-stage load modulated power amplifier with efficiency enhancement at power back-off,” IEEE Trans. Microw. Theory Techn., vol. 69, no. 6, pp. 3107–3119, Jun. 2021. 
[^8]: J. Sun, F. Lin, H. Sun, W. Chen, and R. Negra, “Broadband threestage pseudoload modulated balanced amplifier with power back-off efficiency enhancement,” IEEE Trans. Microw. Theory Techn., vol. 70, no. 5, pp. 2710–2722, May 2022. 
[^9]: Y. Cao and K. Chen, “Pseudo-Doherty load-modulated balanced amplifier with wide bandwidth and extended power back-off range,” IEEE Trans. Microw. Theory Techn., vol. 68, no. 7, pp. 3172–3183, Jul. 2020. 
[^10]: J. Pang et al., “Analysis and design of highly efficient wideband RFinput sequential load modulated balanced power amplifier,” IEEE Trans. Microw. Theory Techn., vol. 68, no. 5, pp. 1741–1753, May 2020. 
[^11]: Y. Cao, H. Lyu, and K. Chen, “Continuous-Mode hybrid asymmetrical load- modulated balanced amplifier with three-way modulation and multi-band reconfigurability,” IEEE Trans. Circuits Syst. I, Reg. Papers, vol. 69, no. 3, pp. 1077–1090, Mar. 2022. 
[^12]: P. Saad and R. Hou, “Symmetrical load modulated balanced power amplifier with asymmetrical output coupling for load modulation continuum,” IEEE Trans. Microw. Theory Techn., vol. 70, no. 4, pp. 2315–2327, Apr. 2022. 
[^13]: V. Qunaj and P. Reynaert, “26.2 A Doherty-like load-modulated balanced power amplifier achieving 15.5dBm average pout and 20% average PAE at a data rate of 18Gb/s in 28nm CMOS,” in Proc. IEEE Int. Solid-State Circuits Conf. (ISSCC), 2021, pp. 356–358.