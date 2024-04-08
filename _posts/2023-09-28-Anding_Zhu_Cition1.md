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

Doherty PA (DPA)  [^4]、[^5]、[^6] 和 **<font color = salmon>负载调制平衡放大器 (LMBA)</font>**  [^7]、[^8]、[^9]、[^10]、[^11]、[^12]、 [^13]，凭借其高输出功率回退效率，引起了人们的广泛关注。 然而，随着回退水平的增加，DPA 负载调制网络的设计变得非常复杂，因为它涉及多段传输线。 

相比之下，这种 LMBA 已被证明是一种可靠的方法，可以通过简单的负载调制网络在深层 OBO 级别上保持比 DPA 更高的效率。 **其架构通过输出耦合器结合了三级放大器，其中包括一个控制放大器（CA）和两个平衡放大器（BA），导致负载调制行为，从而提高回退效率。** 传统的 LMBA 只能提供 6 dB OBO 电平，并且 BA 均作为载波放大器偏置在 AB 类模式 [^7]、[^8]。 为了通过扩展回退范围来提高效率，[^9] 和 [^10] 中提出了伪 Doherty LMBA (PD-LMBA) 和顺序 LMBA (SLMBA)，将 CA 设置为载波，将 BA 设置为峰值放大器。 **然而，CA 负载阻抗保持恒定值，导致线性度恶化，并严重降低 OBO 范围中间的效率**。 在[^11]中，混合非对称LMBA（H-AMBA）可以在更大的回退范围内实现类似于**三级Doherty PA的三峰值效率**。 由于不同的BA为了方便而采用了相同的晶体管，导致功率利用率不足，导致功率成本。 为了充分利用所有单元的功率，[^12]中提出了一种用于 LMBA 的**不对称输出耦合器**。 需要注意的是，隔离端口处BA产生的残余功率会被消耗，从而导致整体PA的饱和效率下降。 虽然这些不同类型的LMBA已逐渐应用于6 GHz以下应用，但由于严格的设计规则检查（DRC）和晶体管高频性能的限制，在毫米波频段实现LMBA架构是一个巨大的挑战 。 由于工艺和对称输出耦合器的限制，[^13]中报道的毫米波Doherty-Like LMBA只能提供较低的OBO电平（6dB）和较小的输出功率。

为了解决上述缺点，本文采用商用 0.15um GaN 工艺设计和制造了带有改进输出耦合器的毫米波 LMBA。 为了进一步提高输出功率和回退效率，提出了一种不对称输出耦合器，使得所提出的LMBA可以在更大的OBO范围内实现效率提高。 与报道的LMBA[^13]相比，我们提出的LMBA表现出更高的OBO效率和输出功率。

## 提出的MMIC LMBA 理论和分析

### A.基于改进正交耦合器的负载调制过程

![image1](https://github.com/WaveDragon/test/assets/78013131/6661e3c7-b5e4-4389-8161-5fcca8ad9a46)
LMBA 的等效框图（建议的 LMBA，C0 $ \ne $ 0.707（3dB）,传统的 LMBA，C0 = 0.707（3dB））。

如图1所示，该LMBA架构由平衡放大器（BA）（PA1和PA2）和控制放大器（CA）组成，它们被视为三个理想的压控电流源。 然后，它们通过两个对称定向耦合器进行耦合，其耦合系数在输入和输出功率处设置为 3dB (C0=0.707)。 简而言之，无论PA1和PA2电流是否相等，CA都可以通过修改耦合系数来实现连续负载调制。 因此，对理想正交耦合器的S、Z矩阵进行分析是非常有必要的，其可以表示为[13]

## 参考文献

[^1]: G. R. Nikandish, R. B. Staszewski, and A. Zhu, “Unbalanced power amplifier: An architecture for broadband back-off efficiency enhancement,” IEEE J. Solid-State Circuits, vol. 56, no. 2, pp. 367–381, Feb. 2021. 

[^2]: M. Bao, D. Gustafsson, R. Hou, Z. Ouarch, C. Chang, and K. Andersson, “A 24–28-GHz Doherty power amplifier with 4-W output power and 32% PAE at 6-dB OPBO in 150-nm GaN technology,” IEEE Microw. Wireless Compon. Lett., vol. 31, no. 6, pp. 752–755, Jun. 2021. 

[^3]: R.-J. Liu et al., “A 24–28-GHz GaN MMIC synchronous Doherty power amplifier with enhanced load modulation for 5G mm-Wave applications,” IEEE Trans. Microw. Theory Techn., vol. 70, no. 8, pp. 3910–3922, Aug. 2022. 

[^4]: D. P. Nguyen, J. Curtis, and A.-V. Pham, “A Doherty amplifier with modified load modulation scheme based on load-pull data,” IEEE Trans. Microw. Theory Techn., vol. 66, no. 1, pp. 227–236, Jan. 2018. 

[^5]: R. Giofre, A. D. Gaudio, W. Ciccognani, S. Colangeli, and E. Limiti, “A GaN-on-Si MMIC Doherty power amplifier for 5G applications,” in Proc. Asia–Pacific Microw. Conf. (APMC), Nov. 2018, pp. 971–973. 
[^6]: J. Xia, W. Chen, F. Meng, C. Yu, and X. Zhu, “Improved threestage Doherty amplifier design with impedance compensation in load combiner for broadband applications,” IEEE Trans. Microw. Theory Techn., vol. 67, no. 2, pp. 778–786, Feb. 2019. 
[^7]: Y. Xu, J. Pang, X. Wang, and A. Zhu, “Three-stage load modulated power amplifier with efficiency enhancement at power back-off,” IEEE Trans. Microw. Theory Techn., vol. 69, no. 6, pp. 3107–3119, Jun. 2021. 
[^8]: J. Sun, F. Lin, H. Sun, W. Chen, and R. Negra, “Broadband threestage pseudoload modulated balanced amplifier with power back-off efficiency enhancement,” IEEE Trans. Microw. Theory Techn., vol. 70, no. 5, pp. 2710–2722, May 2022. 
[^9]: Y. Cao and K. Chen, “Pseudo-Doherty load-modulated balanced amplifier with wide bandwidth and extended power back-off range,” IEEE Trans. Microw. Theory Techn., vol. 68, no. 7, pp. 3172–3183, Jul. 2020. 
[^10]: J. Pang et al., “Analysis and design of highly efficient wideband RFinput sequential load modulated balanced power amplifier,” IEEE Trans. Microw. Theory Techn., vol. 68, no. 5, pp. 1741–1753, May 2020. 
[^11]: Y. Cao, H. Lyu, and K. Chen, “Continuous-Mode hybrid asymmetrical load- modulated balanced amplifier with three-way modulation and multi-band reconfigurability,” IEEE Trans. Circuits Syst. I, Reg. Papers, vol. 69, no. 3, pp. 1077–1090, Mar. 2022. 
[^12]: P. Saad and R. Hou, “Symmetrical load modulated balanced power amplifier with asymmetrical output coupling for load modulation continuum,” IEEE Trans. Microw. Theory Techn., vol. 70, no. 4, pp. 2315–2327, Apr. 2022. 
[^13]: V. Qunaj and P. Reynaert, “26.2 A Doherty-like load-modulated balanced power amplifier achieving 15.5dBm average pout and 20% average PAE at a data rate of 18Gb/s in 28nm CMOS,” in Proc. IEEE Int. Solid-State Circuits Conf. (ISSCC), 2021, pp. 356–358.