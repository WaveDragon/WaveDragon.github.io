---
title: LMBA Summary
author: WaveDragon
date: 2024-04-08 11:11:00 +0800
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

# (2017 MTT)RF-Input Load Modulated Balanced Amplifier With Octave Bandwidth

## 摘要

本文提出了一种**倍频程带宽负载调制平衡放大器 (LMBA)**，它直接在单个调制射频输入上运行。 该架构基于最近提出的LMBA技术，其中在平衡放大器的输出隔离端口施加的控制信号用于调制构成平衡放大器的两个器件的表观负载阻抗。 在我们的方法中，**<font color = salmon>注入的控制信号既用作主动匹配，又用于动态负载调制主要器件，以提高回退时的效率，从而与原始 LMBA 公式相比扩展了动态范围。</font>** 在本文中，我们介绍了一种相位补偿技术，通过该技术，有源匹配和负载调制跟踪封装器件的频率相关最佳负载轨迹。 结果是负载调制功率放大器架构能够在倍频程带宽上执行有源调制匹配。 该技术使用封装器件和现成的混合耦合器在 1.8–3.8 GHz 范围内进行了演示。 概念验证倍频程射频输入 LMBA 的峰值 CW 输出功率为 44 dBm，在 1.8–3.8 GHz 工作频率范围内，峰值功率时的功率附加效率 (PAE) 为 37%–59%，– 6dB 输出回退时为 45%。 该架构的射频输入特性可以使用调制信号进行直接测量； 演示了 3.8 GHz 的 W-CDMA 信号，峰值平均功率比为 9 dB（测得），相邻信道泄漏比为 −30 dBc，平均 PAE 为 18%，平均输出功率为 31 dBm（2 dB 回退） ）。

## 一、介绍

功率放大器 (PA) 应用越来越需要宽带线性操作，例如在载波聚合和其他高数据速率通信应用、成像和雷达中。 此外，现代通信系统的高峰均功率比 (PAPR) 信号需要在较宽的动态范围内运行。 带宽和线性度要求与传统放大器设计的效率不一致。 因此，同时实现宽带操作、线性度和能效的 PA 设计一直是一个长期的挑战。
打破传统 PA 中线性与效率权衡的常见策略是采用基于负载调制的效率增强技术。 这种方法最常见的例子是 Doherty PA [^1] [^2] [^3]，其替代技术包括异相 [^4]、[^5] 和直接负载调制 [^6]、[^7]。 这些技术，特别是流行的 Doherty 架构，通常依赖于限制可实现带宽的窄带匹配结构。 通过修改传统的四分之一波长传输线，宽带 Doherty PA 已被证明具有倍频程带宽 [^1]-[^3]。 同样，通过将组合网络结构吸收到 PA 的匹配网络中，已经探索了异相 PA 的宽带变化 [^4]，其分数带宽高达 33% [^5]。 通过采用更复杂的数字信号分离，可以利用 Doherty 和异相架构之间的连续体将工作频率进一步扩展至超过一个倍频程，[^8] 中演示了 1–3 GHz 操作。
当需要多倍频程带宽时，即使不使用 Doherty 或异相 PA 等功率组合结构，晶体管的输出电容也会使宽带匹配变得复杂。 增加（幅度）的并联电纳需要依赖于频率的匹配，该匹配在史密斯圆图上逆时针移动，与无源元件的顺时针旋转相反。 因此，宽带 OMN 通常包括谐振结构以局部匹配此行为 [^9]，或非福斯特（有源）匹配元件 [^10]。 分布式放大器吸收输出电容，因此可以在多个倍频程内运行，但以牺牲效率为代价[^11]。
最近，<font color = salmon>谢泼德等人。 [^12]、[^13] 介绍了负载调制平衡放大器 (LMBA)，这是一种新的 PA 架构</font>，可以解决传统宽带放大器的缺点。 在 LMBA 中，控制信号被注入平衡放大器配置的输出耦合器的隔离端口，从而在两个主 PA 上产生负载调制。 在[^12]中，该注入信号用于在宽动态功率范围内主动匹配设备，而在[^13]中，该方法得到扩展，表明可以通过修改控制信号的相位来重新配置工作频率。 与 Doherty 和异相架构相比，该架构具有多个显著优势：<font color = salmon>PA 具有相同的负载轨迹并且尺寸相同，并且带宽仅受平衡放大器中使用的 90° 混合耦合器的限制</font>。

迄今为止，已显示在 4.5–7.5 GHz 范围内运行 [^13]，但该方法有可能使用文献中演示的宽带耦合器之一扩展到多倍频程运行，例如 3.4:1 带宽结构 在[^14]中。
与许多效率增强技术（例如，传统的异相和包络跟踪）一样，[^12] 和 [^13] 中描述的 LMBA 并不直接在调制射频输入上运行。 相反，需要外部控制信号来提高效率。 与能够直接在单个调制输入上运行的宽带 Doherty 方法相比，这一特性使得该架构的吸引力较低。 尽管如此，LMBA 因其固有的宽带组合结构而成为宽带 Doherty 方法的有前途的替代方案。

在我们的相关会议论文 [^15] 中，我们演示了原始 LMBA 架构的一种变体，<font color = salmon>其中控制信号直接从单个调制 RF 输入生成，从而形成 RF 输入 LMBA。 我们的方法的另一个特点是控制信号幅度与射频输入一起调制。 相比之下，在[^12]和[^13]中，控制信号功率保持恒定。 调制控制信号功率会导致主 PA 的动态有源负载调制，从而提高回退效率并改善动态范围。</font>

[^15]中的原型仅关注控制信号的幅度控制以提高效率。 在这里，我们扩展了控制信号生成方法，包括自动生成正确的频率相关相位，从而实现倍频程带宽操作。 这种方法的简化原理图如图S 1 所示。我们演示了一种在 1.8–3.8 GHz 频率范围内运行的新型射频输入 LMBA 原型。 PA 在峰值 CW 输出功率下的峰值效率为 37%–59%，在 6 dB 输出回退时为 29%–45%。 测得峰值输出功率为 44 dBm，并且在工作频段上的误差范围在 1 dB 之内。 PA 在 31 dBm 平均功率下的平均效率为 16%–24.9%，使用 9 dB PAPR 3.84 MHz 宽带码分多址 （W- CDMA）信号。

![image1](https://github.com/WaveDragon/test/assets/78013131/e6260e64-ff73-431f-b02e-3f45cf690ed2)
> 图 1. 本文演示的宽带射频输入 LMBA 的简化图。 注入平衡放大器隔离端口的控制信号的相对幅度和相位分别由控制路径的相对PA压缩特性和带通滤波器引入的相对相位控制。

本文的其余部分安排如下。 在第二节中，我们简要回顾了最初提出的 LMBA 的运作情况。 在第三节中，我们描述了最初在[^15]中演示的用于增强回退效率的射频输入方法，以及这里提出的用于宽带操作的新颖的相位控制方法。 第四节详细描述了新型宽带射频输入 LMBA 原型的设计。 本文最后在第五节中给出了使用调制信号的倍频程带宽原型的测量性能，并在第六节中给出了结论。

![image](https://github.com/WaveDragon/test/assets/78013131/c9673470-3cfa-4c82-b914-3e78424047d6)
> 图 2. 最初提出的 LMBA 架构 [^12]。 (a) 简化图。 (b) 控制信号幅度和相位对两个 PA 所见负载阻抗的影响

## 二、 负载调制平衡放大器

[^12] 中描述的 LMBA 基于传统的平衡放大器架构 [^16]，其中两个器件通过输入和输出处的正交混合耦合器进行耦合。 LMBA 与平衡放大器的不同之处在于，LMBA 不是端接输出耦合器的隔离端口，而是将控制信号注入其中（图 2）。 **<font color = salmon>该注入信号用作主动匹配以取代传统的输出匹配网络。</font>**

由于正交耦合器的水平和垂直对称性，注入信号被分成两半并出现在每个分支中 PA 的漏极处。 然后，<font color = salmon>该信号与 PA 生成的输出相互作用，为漏极提供负载阻抗。</font> 对于理想的耦合器，控制信号不会出现在系统的负载处，因为连接负载的端口将显示为隔离的。 在实际场景中，根据耦合器的隔离，负载处会出现可忽略不计的控制信号分量。

与 Doherty 和异相 PA 等其他负载调制架构不同，<font color = salmon>LMBA 的显着优势在于两个 PA 均使用相同的负载阻抗进行调制。 这可以通过注意到主 PA 漏极处的两个信号幅度相等且相位正交来解释，而控制信号（分成相等的两半后）也具有正交相位差。 因此，在每个 PA 的漏极处，输出信号与适当的定相控制信号相互作用，以在两个 PA 的漏极处产生相同的阻抗。 控制信号的幅度和相位与两个主放大器上的有效负载之间的定性关系如图2（b）所示。 [^12]对此操作进行了详细分析。 正如[^12]和[^13]中报道的那样，LMBA架构在宽带操作方面具有巨大的潜力，部分原因是控制信号是外部控制的，并且晶体管在输出端需要很少的匹配或不需要匹配。 该架构中主要的带宽限制因素是耦合器。</font>

值得注意的是，<font color = salmon>控制信号功率不仅在确定 PA 的负载阻抗方面发挥着重要作用，而且在确定总系统效率方面也发挥着重要作用。 在[^12]和[^13]中，控制信号保持恒定功率，选择比峰值输出功率低大约10 dB。 因此，尽管需要在较宽的带宽上运行，但可以假设控制 PA 信号生成的效率相对较高，因为用于生成控制信号的 PA 可以在高效、恒定包络模式下运行。</font> 由于相对功率水平较低，控制信号生成中的任何低效对整体系统效率的影响都可以忽略不计。 缺点是注入输出的恒定控制功率限制了可实现的输出功率动态范围。 通过调制非常低的输出电平的控制信号功率可以直接解决这个问题。

在本文中，与[^12]和[^13]相比，<font color = salmon>控制信号幅度是基于射频输入的幅度调制进行动态调制的。 与原来的 LMBA 相比，这有几个好处。 首先，射频输入 LMBA 通过使用射频电路在电路板上生成控制信号，消除了调制信号所需的额外基带计算。 其次，它提高了回退效率，同时增加了动态范围。 这些优点使 RF 输入 LMBA 成为与高 PAPR 的复杂调制方案一起使用的绝佳选择。</font>

## 三． RF 输入 LMBA 架构


## 结论



[论文地址](https://ieeexplore.ieee.org/document/9173563)

## 参考文献
[^1]: R. Giofrè, L. Piazzon, P. Colantonio, and F. Giannini, “A closedform design technique for ultra-wideband Doherty power amplifiers,” IEEE Trans. Microw. Theory Techn., vol. 62, no. 12, pp. 3414–3424, Dec. 2014. 
[^2]: M. N. A. Abadi, H. Golestaneh, H. Sarbishaei, and S. Boumaiza, “Doherty power amplifier with extended bandwidth and improved linearizability under carrier-aggregated signal stimuli,” IEEE Microw. Wireless Compon. Lett., vol. 26, no. 5, pp. 358–360, May 2016. 
[^3]: R. Darraji, D. Bhaskar, T. Sharma, M. Helaoui, P. Mousavi, and F. M. Ghannouchi, “Generalized theory and design methodology of wideband Doherty amplifiers applied to the realization of an octavebandwidth prototype,” IEEE Trans. Microw. Theory Techn., vol. 65, no. 8, pp. 3014–3023, Aug. 2017. 
[^4]: K. D. Holzer and J. S. Walling, “A one octave, 20 W GaN Chireix power amplifier,” in Proc. WAMICON, Jun. 2014, pp. 1–4. 
[^5]: M. Özen, M. van der Heijden, M. Acar, R. Jos, and C. Fager, “A generalized combiner synthesis technique for class-E outphasing transmitters,” IEEE Trans. Circuits Syst. I, Reg. Papers, vol. 64, no. 5, pp. 1126–1139, May 2017. 
[^6]: W. Hallberg, D. Gustafsson, M. Özen, C. M. Andersson, D. Kuylenstierna, and C. Fager, “A class-J power amplifier with varactor-based dynamic load modulation across a large bandwidth,” in IEEE MTT-S Int. Microw. Symp. Dig., May 2015, pp. 1–4. 
[^7]: K. Chen and D. Peroulis, “Design of adaptive highly efficient GaN power amplifier for octave-bandwidth application and dynamic load modulation,” IEEE Trans. Microw. Theory Techn., vol. 60, no. 6, pp. 1829–1839, Jun. 2012. 
[^8]: C. M. Andersson, D. Gustafsson, J. C. Cahuana, R. Hellberg, and C. Fager, “A 1–3-GHz digitally controlled dual-RF input power-amplifier design based on a Doherty-outphasing continuum analysis,” IEEE Trans. Microw. Theory Techn., vol. 61, no. 10, pp. 3743–3752, Oct. 2013. 
[^9]: K. Chen and D. Peroulis, “Design of broadband highly efficient harmonic-tuned power amplifier using in-band continuous class-F−1/F mode transferring,” IEEE Trans. Microw. Theory Techn., vol. 60, no. 12, pp. 4107–4116, Dec. 2012. 
[^10]: S. Lee, H. Park, K. Choi, and Y. Kwon, “A broadband GaN pHEMT power amplifier using non-Foster matching,” IEEE Trans. Microw. Theory Techn., vol. 63, no. 12, pp. 4406–4414, Dec. 2015.
[^11]: C. F. Campbell, S. Nayak, M.-Y. Kao, and S. Chen, “Design and performance of 16–40 GHz GaN distributed power amplifier MMICs utilizing an advanced 0.15 μm GaN process,” in IEEE MTT-S Int. Microw. Symp. Dig., May 2016, pp. 1–4. 
[^12]: D. J. Shepphard, J. Powell, and S. C. Cripps, “An efficient broadband reconfigurable power amplifier using active load modulation,” IEEE Microw. Wireless Compon. Lett., vol. 26, no. 6, pp. 443–445, Jun. 2016. 
[^13]: D. J. Shepphard, J. Powell, and S. C. Cripps, “A broadband reconfigurable load modulated balanced amplifier (LMBA),” in IEEE MTT-S Int. Microw. Symp. Dig., Jun. 2017, pp. 1–4. 
[^14]: A. M. Abbosh and M. E. Bialkowski, “Design of compact directional couplers for UWB applications,” IEEE Trans. Microw. Theory Techn., vol. 55, no. 2, pp. 189–194, Feb. 2007. 
[^15]: P. Pednekar and T. Barton, “RF-input load modulated balanced amplifier,” in IEEE MTT-S Int. Microw. Symp. Dig., Jun. 2017, pp. 1–4. 
[^16]: K. B. Niclas, W. T. Wilser, R. B. Gold, and W. R. Hitchens, “Application of the two-way balanced amplifier concept to wide-band power amplification using GaAs MESFET’s,” IEEE Trans. Microw. Theory Techn., vol. 28, no. 3, pp. 172–179, Mar. 1980. 
[^17]: R. Quaglia, D. J. Shepphard, and S. Cripps, “A reappraisal of optimum output matching conditions in microwave power transistors,” IEEE Trans. Microw. Theory Techn., vol. 65, no. 3, pp. 838–845, Mar. 2017. 
[^18]: J. Moon, J. Son, J. Lee, and B. Kim, “A multimode/multiband envelope tracking transmitter with broadband saturated amplifier,” IEEE Trans. Microw. Theory Techn., vol. 59, no. 12, pp. 3463–3473, Dec. 2011. 
[^19]: N. Tuffy, L. Guan, A. Zhu, and T. J. Brazil, “A simplified broadband design methodology for linearized high-efficiency continuous class-F power amplifiers,” IEEE Trans. Microw. Theory Techn., vol. 60, no. 6, pp. 1952–1963, Jun. 2012. 
[^20]: K. Chen and D. Peroulis, “Design of highly efficient broadband class-E power amplifier using synthesized low-pass matching networks,” IEEE Trans. Microw. Theory Techn., vol. 59, no. 12, pp. 3162–3173, Dec. 2011. 
[^21]: G. L. Matthaei, “Tables of Chebyshev impedance–transforming networks of low-pass filter form,” Proc. IEEE, vol. 52, no. 8, pp. 939–963, Aug. 1964. 
[^22]: P. H. Pednekar and T. W. Barton, “Dual-band Chireix combining network,” in Proc. Texas Symp. Wireless Microw. Circuits Syst., Mar. 2016, pp. 1–4. 
[^23]: P. Wright, J. Lees, J. Benedikt, P. J. Tasker, and S. C. Cripps, “A methodology for realizing high efficiency class-J in a linear and broadband PA,” IEEE Trans. Microw. Theory Techn., vol. 57, no. 12, pp. 3196–3204, Dec. 2009. 

[^24]: P. Saad, C. Fager, H. Cao, H. Zirath, and K. Andersson, “Design of a highly efficient 2–4-GHz octave bandwidth GaN-HEMT power amplifier,” IEEE Trans. Microw. Theory Techn., vol. 58, no. 7, pp. 1677–1685, Jul. 2010.




















