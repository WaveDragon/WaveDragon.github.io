---
title: (2017 MTT)RF-Input Load Modulated Balanced Amplifier With Octave Bandwidth
author: WaveDragon
date: 2024-04-08 11:11:00 +0800
categories: [Blogging, LMBA]
tags: [PA]
math: true
mermaid: true
password_protect: false
# image:
#   path: /commons/devices-mockup.png
#   width: 800
#   height: 500
#   alt: Responsive rendering of Chirpy theme on multiple devices.
---


## 摘要

本文提出了一种**倍频程带宽负载调制平衡放大器 (LMBA)**，它直接在单个调制射频输入上运行。 该架构基于最近提出的LMBA技术，其中在平衡放大器的输出隔离端口施加的控制信号用于调制构成平衡放大器的两个器件的表观负载阻抗。 在我们的方法中，**<font color = salmon>注入的控制信号既用作主动匹配，又用于动态负载调制主要器件，以提高回退时的效率，从而与原始 LMBA 公式相比扩展了动态范围。</font>** 在本文中，我们介绍了一种相位补偿技术，通过该技术，有源匹配和负载调制跟踪封装器件的频率相关最佳负载轨迹。 结果是负载调制功率放大器架构能够在倍频程带宽上执行有源调制匹配。 该技术使用封装器件和现成的混合耦合器在 1.8–3.8 GHz 范围内进行了演示。 概念验证倍频程射频输入 LMBA 的峰值 CW 输出功率为 44 dBm，在 1.8–3.8 GHz 工作频率范围内，峰值功率时的功率附加效率 (PAE) 为 37%–59%，– 6dB 输出回退时为 45%。 该架构的射频输入特性可以使用调制信号进行直接测量； 演示了 3.8 GHz 的 W-CDMA 信号，峰值平均功率比为 9 dB（测得），相邻信道泄漏比为 −30 dBc，平均 PAE 为 18%，平均输出功率为 31 dBm（2 dB 回退） ）。

## 一、介绍

功率放大器 (PA) 应用越来越需要宽带线性操作，例如在载波聚合和其他高数据速率通信应用、成像和雷达中。 此外，现代通信系统的高峰均功率比 (PAPR) 信号需要在较宽的动态范围内运行。 带宽和线性度要求与传统放大器设计的效率不一致。 因此，同时实现宽带操作、线性度和能效的 PA 设计一直是一个长期的挑战。
打破传统 PA 中线性与效率权衡的常见策略是采用基于负载调制的效率增强技术。 这种方法最常见的例子是 Doherty PA [^1] [^2] [^3]，其替代技术包括异相 [^4]、[^5] 和直接负载调制 [^6]、[^7]。 这些技术，特别是流行的 Doherty 架构，通常依赖于限制可实现带宽的窄带匹配结构。 通过修改传统的四分之一波长传输线，宽带 Doherty PA 已被证明具有倍频程带宽 [^1]-[^3]。 同样，通过将组合网络结构吸收到 PA 的匹配网络中，已经探索了异相 PA 的宽带变化 [^4]，其分数带宽高达 33% [^5]。 通过采用更复杂的数字信号分离，可以利用 Doherty 和异相架构之间的连续体将工作频率进一步扩展至超过一个倍频程，[^8] 中演示了 1–3 GHz 操作。
当需要多倍频程带宽时，即使不使用 Doherty 或异相 PA 等功率组合结构，晶体管的输出电容也会使宽带匹配变得复杂。 增加（幅度）的并联电纳需要依赖于频率的匹配，该匹配在史密斯圆图上逆时针移动，与无源元件的顺时针旋转相反。 因此，宽带 OMN 通常包括谐振结构以局部匹配此行为 [^9]，或非福斯特（有源）匹配元件 [^10]。 分布式放大器吸收输出电容，因此可以在多个倍频程内运行，但以牺牲效率为代价[^11]。
最近，<font color = salmon>谢泼德等人。 [^12] , [^13] 介绍了负载调制平衡放大器 (LMBA)，这是一种新的 PA 架构</font>，可以解决传统宽带放大器的缺点。 在 LMBA 中，控制信号被注入平衡放大器配置的输出耦合器的隔离端口，从而在两个主 PA 上产生负载调制。 在[^12]中，该注入信号用于在宽动态功率范围内主动匹配设备，而在[^13]中，该方法得到扩展，表明可以通过修改控制信号的相位来重新配置工作频率。 与 Doherty 和异相架构相比，该架构具有多个显著优势：<font color = salmon>PA 具有相同的负载轨迹并且尺寸相同，并且带宽仅受平衡放大器中使用的 90° 混合耦合器的限制</font>。

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

## 三、 RF 输入 LMBA 架构

RF 输入 LMBA 架构的目标是从 **RF 输入自动生成调制控制信号**。 为了实现这一目标，首先重要的是确定控制信号所需的特性。 在本文中，我们将控制信号的生成分为两个部分：**幅度（负载）调制和相位（频率）控制**。 该架构的设计使得这些组件的设计可以独立处理。 在本节中，我们首先回顾相关会议论文 [^15] 中提出的幅度控制，然后介绍一种支持宽带操作的频率相关相位补偿。

### A. 负载调制的幅度控制

如图2所示，增加控制信号幅度 $\left | P_{ctrl} \right | $ 会增加反射系数幅度 $\left| \Gamma \right | $ ，而增加控制信号相位 $\left | \angle P_{ctrl} \right | $ 会在史密斯圆图中逆时针旋转。 幅度相关控制信号的目标是正确合成史密斯圆图中的轨迹，该轨迹对应于至少 6 dB 输出功率动态范围内的高效运行.
在[^13]中，假设PA不具有任何输出匹配，即输出直接连接到晶体管的漏极，而在[^12]中，**漏极处仅包含用于偏置的扼流圈**。 相反，在这里，我们假设分支 PA 还可以包括一定量的预匹配（替代地或附加地，可以设计用于非 50Ω 阻抗的耦合器作为预匹配的手段）。 此外，在实践中，将包括偏置三通，并且晶体管和耦合器之间可能需要一定的互连长度。 在以下分析中，**所有阻抗和负载牵引仿真均以耦合器的输入端口为参考，因为这是考虑注入控制信号影响的参考平面**。 对于本文中的原型（如第 IV 节所述），Main PA 包括偏置 T 形接头和微带线（用于机械布局目的）。
**我们首先假设支路 PA 与 $\left| \Gamma \right | $ =0 时的峰值输出功率匹配。 当输出功率回退 6 dB 时，可以找到最佳的复反射系数 $ \Gamma_{BO}  $ （通过负载牵引模拟或测量，或如 [^17] 中的分析），从而最大化功率附加效率 (PAE)。 然后，所需的负载阻抗轨迹将通过 $ \Gamma_{BO} $ 径向连接史密斯圆图的中心**。 图 3 显示了一组负载拉动等值线示例。在每幅图中，最大驱动条件下的输出功率等值线以蓝色显示，而 PAE 等值线（红色）以 6 dB OBO（我们的目标背压）显示。 关闭电源级别。 PAE 负载牵引轮廓是在回退时而不是在峰值输出功率时进行仿真的，因为本文的重点是提高目标回退功率下的效率，对应于信号的预期 PAPR。 有源负载调制的功能是将匹配从低功率下的最佳PAE点（其中PAE优先）转变为高功率下的最佳功率匹配（其中功率优先）。 在本例中，为具有图3（a）的负载拉动特性的设备设计了匹配网络，以产生图3（b）所示的负载拉动特性。 现在，所得负载轨迹在史密斯圆图中是径向的，因此仅取决于控制信号的幅度，而控制信号的相位是固定的。

![image3](https://github.com/WaveDragon/test/assets/78013131/de0d5e2d-49a1-445e-a933-96af057bfd47)

>图 3. 示例负载牵引模拟和阻抗轨迹，说明负载调制的控制信号生成，在输出耦合器输入的参考平面处获取。 最大驱动条件下的输出功率等值线显示为蓝色，而 PAE 等值线显示为 6dB OBO，我们的目标回退功率水平 (a) 没有输出匹配网络的器件的负载牵引和 (b) 负载牵引 PA 与 $ |\Gamma|=0  $ 处的峰值功率匹配，从而产生所需的径向负载阻抗轨迹。

为了产生所需的径向载荷轨迹，**需要输入功率和控制信号功率之间存在反比关系**。 也就是说，控制信号幅度必须随着所需输出功率的降低而增加。 使用射频电路技术很难实现这种关系。 然而，值得注意的是，与总输出功率相比，**控制信号功率的相对幅度必须降低。 也就是说，控制信号功率不需要在绝对意义上减小。为了实现这种关系，我们利用控制 PA 的压缩特性来创建依赖于输入功率的相对控制功率。** 这种方法如图 4 所示。控制路径设计为在较低功率水平下饱和，以便相对控制功率 Prel 根据需要随输入驱动而减小。 如第 IV 节详细描述的，两个分支中的不同饱和特性是使用不同尺寸的封装晶体管（此处为 10W 和 6W 器件）实现的。

![image4](https://github.com/WaveDragon/test/assets/78013131/c3f75df7-469e-4484-be80-2b6c5bda9365)

>图 4.动态负载调制的幅度控制方法。 控制路径 PA 具有非线性 AM-AM 响应，因此 Pctrl 与主 PA 功率 Pmain,1,2 的相对幅度随着 Pin 的增加而减小。 (a) RF 输入 LMBA 的简化示意图，显示了绘制负载牵引等值线的参考平面 $ Z_{ref} $ 。 (b) 主输出功率和控制输出功率的代表图。

主 PA 输出功率与控制功率之比 $\left| P_{rel} \right | $  定义为 $\left| P_{rel} \right | = \left| P_{main} \right |  /\left| P_{ctrl} \right | $ ，由输入功率电平、主 PA 和控制 PA 的相对大小以及输入分配器的权重决定（此处， 使用 3 dB 等分）。 如图 4 所示，$\left| P_{rel} \right | $  的设计范围为低输入功率时的约 2.5 dB 至高输入功率时的约 6 dB。 显然，采用所提出的方法，提供给两个 PA 的大信号反射系数将永远不会达到 $\left| \Gamma \right |  =0 $ ，因为这种情况将对应于 $\left| P_{rel} \right |   =∞ $ 。 结果是图3（b）所示的概念功率匹配并不理想； 相反，**在实践中应该设计匹配网络，使得不与史密斯圆图中心相交的径向负载轨迹提供所需的输出功率动态范围**。 **这种新的匹配方法放宽了对主 PA 输出匹配网络的设计要求，不再需要 50Ω 的宽带匹配**。 图 5 说明了为 [^15] 中的原型设计的（有限）负载调制动态范围。 **<font color = salmon>如果可以容忍峰值输出功率的降低，则可以消除输出匹配网络，从而对尺寸和损耗产生相应的好处。</font>**

![image5](https://github.com/WaveDragon/test/assets/78013131/82b01430-e45f-439e-8f3a-927eeb2d46d0)

>图 5. 实际上，$ P_{rel} $ 的有限范围限制了负载调制的动态范围。 因此，不一定需要输出匹配网络。

### B. 宽带操作

宽带 PA 设计的主要挑战是，**<font color = salmon>与峰值效率对应的负载阻抗在史密斯圆图中逆时针移动，而用于匹配的无源元件是分散的（顺时针旋转）</font>** 。 图 6 显示了实验验证中使用的主要 PA 的负载牵引模拟示例集，说明了峰值 PAE 和 PAE 轮廓的逆时针旋转。 这里使用 PAE 等值线作为目标阻抗，因为本文的重点是退避时的效率； 实验工作（第五节）表明，整个频段的峰值输出功率也保持在大约 1 dB 之内。 本例中的主要 PA 包括 Wolfspeed CGH40010F GaN 器件、一个简单的偏置 T 形件和一个微带互连（除了器件本身之外，它还贡献色散）。**<font color = salmon>逆时针旋转可以简单地理解为由器件输出电容引起的：该并联电抗的大小随着频率而减小，需要补偿感性负载减小。 实际上，PA 输出匹配网络中任何附加的与频率相关的相位都会影响这种旋转随频率发生的速度</font>**


![image6](https://github.com/WaveDragon/test/assets/78013131/8ff29c03-b1ac-4d27-81c0-86840175342a)

>图 6. 主 PA 的最佳 PAE 轮廓在 1.8–3.8 GHz 范围内的频率变化，其中包括 10 W 器件、偏置 T 形接头和到达耦合器的短互连长度。 逆时针旋转使得与传统无源元件的匹配具有挑战性。




为了**在逆时针旋转时跟踪最佳 PAE 点，控制信号相位必须随频率增加**（见图 2）。 与第 III-A 节中描述的幅度控制方法一样，**必须控制两个路径的相对相位**。 因此，两种可能性是在控制路径中使用**非福斯特网络，使其相位随频率而增加，或者在主 PA 路径中插入额外的负相移，以使这些路径的相位随频率更快地减小。 在每种情况下，控制路径的相对相位都会随着频率而增加**。 后一种方法类似于[^15]中用于幅度控制的方法，其中通过塑造控制路径的压缩特性来增加控制信号的相对功率。 我们将在这里重点讨论这种方法，但请注意，由于相位补偿，整个系统可能会增加色散，使其不适合非常宽带的瞬时信号。 为了生成正确的控制信号相位响应而不影响负载调制机制，使用带通滤波器，其通带涵盖感兴趣的频率范围。**滤波器阶数和拓扑结构决定了频率相关的相位特性**。 如图7所示，我们可以根据器件的负载牵引找到所需的相位特性。 在实践中，其他网络（控制 PA、互连等）中任何现有的分散也必须予以考虑和补偿。 第四节描述了实验原型的补偿滤波器的拓扑选择和设计。

![image7](https://github.com/WaveDragon/test/assets/78013131/be0777d2-c043-4997-b184-982d15f72424)

>图 7. 控制信号需要与频率相关的相移来匹配图 6 所示的逆时钟范围最佳负载旋转。该相位特性在我们的原型中使用带通滤波器实现。

## 四、 宽带射频输入 LMBA 设计

### A. 主路径平衡PA

平衡 PA 设计包括输入端的匹配网络和输出端的偏置 Tee 的设计。 两个 PA 完全相同，并且偏置在相同的漏极电流下，以确保它们受到相同的负载调制。 商用现成耦合器（Anaren 的 XMC0204F1-03）用于平衡放大器以及输入分离。
1.  输入匹配：基于传输线的多级低通匹配网络已在许多宽带PA中使用[^18]、[^19]。 这种网络的设计可以基于低通原型[^9]、[^20]来完成。 遵循[^20]中建议的方法来设计输入匹配网络，使其在 1.8 至 4 GHz 频段上运行。 本文采用**四级低通滤波器拓扑来实现输入匹配网络**，每级由串联L和并联C元件组成。 每个阶段的元素值可以从[^21]中给出的表中找到。 图 8(a) 显示了输入匹配网络中使用的低通滤波器拓扑。 匹配网络是通过将集总元件值转换为分布式元件值来实现的，以准确地实现所需的元件值。 串联电感器由高阻抗线路实现，而并联C由两个并联开路短截线实现，如图8(b)所示。 **<font color = salmon>栅极偏置网络通过网络第一级的隔直电容器和网络第四级的射频扼流电感器来实现。 短截线的最终长度和宽度经过调整，以吸收射频和直流模块以及器件封装的寄生效应。</font>**
   
2. 输出匹配和偏置 Tee：在倍频程带宽 RF 输入 LMBA 架构中，主 PA 输出处的任何匹配网络都必须在整个倍频程频带上运行，并且会在主路径中增加不均匀的相位色散。 这种不均匀的相位分散抑制了相位跟踪，因此是不期望的。 因此，在我们的设计中，晶体管不匹配，并且输出端仅包含一个偏置器。 如果控制 PA 关闭，两个主 PA 只会看到偏置 T 形接头，后面是输出处的未端接耦合器。 换句话说，在没有控制信号的情况下，主 PA 在输出端的匹配度会很差。 **仅当控制信号有效时，才会向两个 PA 提供正确的负载。 这种方法也被用在之前的 LMBA 实现中 [^12]、[^13]、[^15]。**

![image8](https://github.com/WaveDragon/test/assets/78013131/d8560485-13f1-47b3-9270-1a9687068471)

>图8 平衡放大器的输入匹配网络。 (a) 低通原型网络拓扑。 (b) 等效分布式元件网络。


偏置 T 形管的原理图位于输出端，如图 9 所示。15-nH RF 模块是使用 Coilcraft 高自谐振频率、低串联电阻 (ESR) 电感器实现的。 直流阻断是通过 120pF Murata 电容器实现的。 根据这些集总元件的值，主路径中不可避免地添加一些相位； 该阶段必须在控制路径中得到补偿。

![image9](https://github.com/WaveDragon/test/assets/78013131/80020d24-62db-418e-9749-1f86ae4b1a4c)

>图9.平衡放大器输出匹配示意图。

### B. 控制路径 PA

宽带 LMBA 架构面临的一项挑战是它需要一个宽带 PA 来传输控制信号。 在[^13]中，控制路径功率限制为1W（与至少39.5dBm的总输出功率相比），因此控制信号生成的低效率不会显着影响总体发射机功率。 在这里，我们将控制信号提高 30 dBm，在总输出功率的 11–13 dB 范围内。

为了实现宽带运行，在 AB 类偏置的 6W Wolfspeed CGH40006P GaN 晶体管上执行了模拟负载牵引，工作静态漏极电流为 100mA。 在 1.8-4 GHz 频段的离散频率下执行基本负载牵引，以确定 PAE 的最佳阻抗。 此外，在 2f0 处模拟了二次谐波负载牵引，其中 f0 是基带 (2.9 GHz) 的中心，以进一步提高工作频率范围内的 PAE。 该器件的输出端采用非均匀、阶梯式阻抗拓扑。

由于最佳输出阻抗的非福斯特类型行为，使用无源元件很难实现倍频程带宽的完美匹配。 因此，进行了灵敏度分析以确定低于最佳终端阻抗的影响。 对于该器件，我们发现 3 GHz 以上的频率对负载端接更加敏感，因此在此范围内的匹配时要更加小心。 输出端总共使用了三段传输线，以降低复杂性并实现优化。 输出网络和目标阻抗的仿真如图 10 所示。

![image10](https://github.com/WaveDragon/test/assets/78013131/987dfd98-0d4b-4e2c-965d-3ce9b40e2baa)
>图 10. 具有相应目标阻抗（用“x”标记显示）的控制 PA（用“o”标记显示）的输出网络响应。

器件的Source Pull是通过连接在 1.8-4 GHz 带宽上的输出匹配网络来执行的。 然后将结果用于在输入处合成匹配网络。 据观察，输入端的匹配率高于输出端的匹配率。 栅极偏置网络被吸收到输入匹配中，以在输入处具有混合宽带网络。 最终输出功率、增益和 PAE 如图 11 所示，CW 输入功率为 30 dBm。 6W 晶体管在 20V 电源下运行，以保持其饱和（如第 III-A 节中所述）。 这降低了控制 PA 的增益，但保持了较高的控制路径效率，并为发生动态负载调制生成适量的控制功率。

![image11](https://github.com/WaveDragon/test/assets/78013131/5e466b4f-6820-4d53-9819-e702421f3bb1)

>图 11. CW 输入为 30 dBm 的宽带控制 PA 的模拟输出功率、增益和 PAE。

### C. 频率补偿滤波器

**RF 输入 LMBA [^15] 和此处介绍的倍频程带宽 RF 输入 LMBA 之间的主要架构差异是带通滤波器**。 滤波器响应通过提供**色散补偿**来实现倍频程 LMBA 的宽带操作。 带通滤波器的相位响应在频带上线性变化，允许控制路径和主路径之间的相对相位随着工作频率的变化而动态变化。**滤波器相位（随频率变化）变化的斜率可由滤波器的三个因素控制：带宽、拓扑和阶数。** 对于该原型，选择了**巴特沃斯拓扑**，因为它在通带中具有平坦的响应和最小的纹波。 通带中的纹波可能会干扰幅度控制。

滤波器的阶数是根据系统所需的斜率来选择的。 作者之前在双频带 Chireix 组合网络的演示中利用了相位斜率对滤波器阶数的依赖性 [^22]。 设置滤波器的阶数后，可以选择滤波器的带宽以精确调整相位斜率。 滤波器带宽的最小限制由系统的总带宽设置。 为了微调相位响应，唯一的可能是增加滤波器的带宽。 在本例中，滤波器设计为在 1.8 至 3.8 GHz 的带宽上运行。 图 12 显示了模拟的整体滤波器性能。 通带衰减优于0.2 dB。 1.8 和 3.8 GHz 是滤波器的转角频率，其中通带衰减大约下降 1 dB。 相位响应的斜率为负 6.2°/100 MHz，这提供了所需的相位响应，以补偿图 7 所示的整个带宽上的频率相关相移。 适量的相位斜率沿逆时针方向跟踪负载相位轨迹，以实现宽带运行。

![image12](https://github.com/WaveDragon/test/assets/78013131/33872a4c-336c-45ee-a5d8-18d3269a7dc7)

>图 12. 巴特沃斯带通滤波器的幅度和相位响应。

![image13](https://github.com/WaveDragon/test/assets/78013131/bf8138c7-d5a5-4425-8bd5-16b3dfa077cd)

>图 13. 用于相位补偿的基于传输线的巴特沃斯滤波器实现。


所需的宽带宽使得滤波器设计成为一项具有挑战性的任务； 随着滤波器带宽的增加，滤波器元件（无论是集总的还是分布式的）变得难以实现。 在此原型中，使用了集总和分布式组件的混合网络。 图 13 显示了我们实验原型中使用的巴特沃斯滤波器的实现。

### D. 模拟宽带射频输入 LMBA 性能

图 14 显示了所制作的倍频程带宽射频输入 LMBA 设计的照片。PA 的性能基于 EM 提取和制造商提供的组件模型进行仿真，以验证负载轨迹控制方法。 在图 15 中，将 1.8–3.8 GHz 范围内的模拟负载轨迹与频率扫描时平衡放大器器件的最佳 PAE 轮廓进行了比较。 负载轨迹在整个带上跟踪逆时针旋转。 由于控制 PA 特性相对于主平衡放大器特性的变化，负载调制的程度在整个频段内有所不同。 如图 15 所示，该设计优先考虑频段高端的负载调制，预计整体性能最低。 PAE、输出功率和增益的仿真性能如图 1 和 2 所示。 图16-18。 我们注意到，在这些模拟以及第五节中的测量结果中，所提供的 PAE 包括所有直流电源的消耗。 也就是说，控制 PA 功耗包含在所有给出的数字中。

![image14](https://github.com/WaveDragon/test/assets/78013131/4d9c72a2-6e7b-4b2d-adad-cc6f9b7edadc)

>图 14. 倍频程带宽 RF 输入 LMBA 原型的照片，该原型实现了 1.8–3.8 GHz 操作。

![image](https://github.com/WaveDragon/test/assets/78013131/101a6f28-1d4e-4a83-8cd7-68bcbd85b9c6)

>图 15. 器件最佳 PAE 轮廓（蓝色轮廓）在 1.8–3.8 GHz 范围内的频率变化，以及相同频率范围内平衡放大器晶体管的负载轨迹（红色、棕色轨迹）。 负载轨迹在倍频程范围内跟踪 PAE 目标的逆时针旋转。

![image](https://github.com/WaveDragon/test/assets/78013131/9836c3aa-4835-44e8-a766-0a22f02c04cf)




## 测试结果


## 结论

本文提出的**频率补偿方法利用带通滤波器的色散来创建能够在大于倍频程带宽上运行的 RF 输入 LMBA**。 这种方法与我们用于负载调制的幅度控制方法相关，其重点是控制 LMBA PA 的控制路径和主路径的相对相位。 这种新颖的架构消除了先前宽带 LMBA 系统实现所需的外部信号生成控制信号的需要。 **该方法的优点包括降低系统复杂性以及能够直接使用许多现有的校准和线性化技术**。
本文中的概念验证原型是使用封装的 GaN 晶体管实现的，并在 1.8-3.8-GHz 工作范围内演示了该技术。 该系统的峰值漏极效率达到 70%，并且在整个频段的峰值输出功率下漏极效率高于 46%。 通过负载调制维持的回退效率在整个频带内高于 33%。 此外，由于该架构的射频输入特性，可以使用调制信号轻松测量原型。 对于 9 dB PAPR、3.85 MHz W-CDMA 信号，PA 展示了整个频段的 ACLR 范围为 -26 至 -30 dB，无需线性化。

本文提出的射频输入 LMBA 架构并不特定于该特定频段或带宽。 相反，原型的频率范围是根据可用的商用现成耦合器和封装设备来选择的。 **通过替代耦合器可以实现更宽的带宽； 在这种情况下，主要的挑战将是设计具有适当通带和相位响应的宽带滤波器。** 在某种程度上，可以通过使用裸芯片或集成器件，以及通过最小化耦合器和互连的尺寸来减轻这一挑战，以减少工作范围内最佳负载阻抗轮廓的频率变化。 **同样，通过注意尽量减少色散，可以获得更高的工作频率，从而使 MMIC 实施具有吸引力。 对该拓扑结构的一项有趣的进一步研究是了解大于倍频程实现的工作频率范围的限制。**





[<font color = salmon font size = 36>论文地址</font>](https://ieeexplore.ieee.org/document/8038246) 

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























