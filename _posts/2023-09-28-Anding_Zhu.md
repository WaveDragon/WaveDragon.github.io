---
title: Unbalanced Power Amplifier An Architecture for Broadband Back-Off Efficiency Enhancement
author: WaveDragon
date: 2023-9-28 11:11:00 +0800
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

## 摘要
摘要：在本文中，我们提出了一种新的宽带功率放大器 (PA) 架构，具有回退效率增强功能，支持非常宽的调制带宽。 非平衡 PA 由两个协作的子 PA 组成，使用兰格耦合器作为输入功率分配器和输出功率组合器。 PA 操作由晶体管的宽度比和兰格耦合器的耦合系数控制。**输出功率回退（OPBO）水平由晶体管的宽度比和输出耦合器的耦合系数给出，而最大效率在回退点实现。** 与传统的 Doherty PA 相比，这些功能提供了更大的设计灵活性，其中 OPBO 只能通过晶体管的宽度比来设置，并且在峰值功率下实现最大效率。 使用**宽带谐波匹配网络，主子 PA 和辅助子 PA 以连续模式运行，以提高宽带宽上的效率**。 采用 250 nm GaN-on-SiC 工艺实现的完全集成非平衡 PA 可实现 32.2–34.3 dBm 输出功率，峰值功率时效率为 27%–37%，5–6 dB 时效率为 27%–40% 回退，跨 4.5–6.5 GHz。 该 PA 为具有 100-/200-MHz 带宽、7.2-dB PAPR 和 25.5- 的 256-QAM 信号提供 3.7/4.5% (−28.6/−26.9 dB) rms 误差矢量幅度 ($ EVM_{rms} $) 和 30% 平均效率。 dBm 平均输出功率，不使用任何预失真。

Index Terms — 回退、平衡放大器、宽带电路、耦合器、第五代 (5G)、GaN、负载调制、功率放大器 (PA)。

## 介绍

移动通信系统的快速发展，例如新的第五代 (5G) 标准，对发射器和接收器射频 (RF) 电路提出了严格的要求。 功率放大器 (PA) 作为发射机最关键的组件，应满足 5G 系统的挑战性条件。 对于 5G 中使用的具有大峰均功率比 (PAPR) 和宽带宽的复杂调制信号，PA 首先应该即使在回退时也能提供高效率，其次要保持高幅度和相位线性度，以高效地 放大并传递高质量信号。

为了增强回退效率，开发了多种 PA 架构，其中最著名的是 **Doherty PA、异相 PA、包络跟踪 PA、负载调制平衡 PA 和可重构 PA**[1]–[15]。 Doherty PA 是现代通信中最流行的架构，主要是因为其电路架构简单，具有单输入射频信号，**并且可以通过适当调整两个放大器路径中的偏置和相移来提供线性幅度和相位特性**， 即主要和辅助子 PA [2]。 Doherty PA 依靠阻抗逆变器在峰值功率和回退时为主晶体管提供最佳负载阻抗。 阻抗逆变器通常被实现为四分之一波长传输线或其等效集总电路元件。 **<font color = salmon> 然而，这些电路的带宽较窄，限制了总体 DPA 带宽 [3]。 人们开发了多种技术来扩展 Doherty PA 的带宽，包括负载调制网络中传输线的修改阻抗、两段峰值网络、寄生电容补偿和双输入 Doherty PA 结构 </font>** [3]。 [4] 和 [5] 中提出了电压模式 Doherty PA，其中使用变压器组合两个开关电容器 PA，并且由于不使用阻抗逆变器，因此在较宽的带宽上实现了回退效率增强。 然而，电路操作以开关为基础，这些开关可能无法在高频（例如毫米波）下提供良好的性能，或者可能无法在给定的工艺中以足够低的损耗提供。 电压模式 Doherty PA 可以在低 RF 频率下提供宽带宽，但在较高频率下，可能很难在宽带宽上维持辅助晶体管的短路输出阻抗。

异相 PA 的工作原理是将输入信号分成两个并行信号，其相位取决于输入幅度，然后 **<font color = salmon>通过适当的负载阻抗组合放大（和饱和）的信号</font>** [6]。 带宽主要受所需负载阻抗的频率响应的限制。 因此，异相PA通常具有较窄的带宽，并且很少用于无线通信中。 包络跟踪 PA 对包络信号的时序对齐很敏感，这对于宽调制带宽来说可能具有挑战性 [7]。

**<font color = salmon>负载调制平衡放大器架构是最近开发的一种用于增强回退效率的方法[10]-[13]，其中平衡 PA 晶体管的负载阻抗是使用施加到 PA 隔离端口的信号进行调制的。</font>** 输出混合耦合器。 与 Doherty PA 相比，由于采用了不依赖阻抗逆变器的不同负载调制方法，该 PA 架构可以提供更宽的带宽。 在最初的实现中，附加信号是通过辅助放大器与外部射频信号生成的，并且必须保持相对于输入信号的特定幅度/相位关系才能实现预期操作[10]。 附加信号可以从输入信号生成，以实现单个射频输入 PA [11]。 然而，**需要额外的 PA 和宽带相移电路，这会增加芯片面积、降低效率并限制带宽**。

可重新配置的 PA 可以在较宽的带宽上提供回退效率增强，并提高对负载电压驻波比 (VSWR) 效应的耐受性 [14]–[16]。 **Doherty PA 还可以使用可重构电路来扩展负载调制网络的带宽，并调整输入网络以实现相位均衡，以提高效率** [17]。 这些可重新配置结构的缺点是与**额外控制和调谐电路相关的开销**。 在本文中，我们提出了一种基于改进的平衡放大器的新 PA 架构，具有宽带回退效率增强功能。 新的 PA 架构称为非平衡 PA，由两个协作的子 PA 组成，其中兰格耦合器用作输入功率分配器和输出功率组合器。 PA 操作由晶体管的宽度比和耦合器的耦合系数控制。 该架构不需要阻抗逆变器（例如 Doherty PA 中的阻抗逆变器），也不需要额外的 PA 和相移电路（例如负载调制平衡 PA 中的）。 因此，它可以实现宽带操作。 本文的结构如下。 在第二节中，我们介绍了不平衡 PA 的运行理论。 电路设计过程和细节在第三节中给出。 我们在第四节中提供了完全集成的 GaN PA 原型的测量结果，然后在第五节中进行了总结。

## 不平衡PA结构

### A.原理说明
![image](https://github.com/WaveDragon/test/assets/78013131/057b12d8-5144-4546-8fdc-018c370a2ee8)

所提出的不平衡 PA 架构如图 1 所示，其中正交混合耦合器用作信号分配器和信号组合器。 我们首先对 PA 操作进行直观描述，然后对其回退效率增强和线性操作进行严格分析。 **<font color = salmon>输入功率根据输入耦合器的耦合系数在主子 PA 和辅助子 PA 之间分配</font>**。 **主子PA和辅助子PA分别偏向B类和C类模式。 因此，在低输入功率电平时，只有主子PA工作，辅助子PA关闭。 通过增加输入功率电平，辅助子 PA 逐渐开启并开始贡献输出功率。 此时，主子PA可以处于线性操作或饱和状态。 为了最大化回退时的效率，主子PA应处于饱和开始处，即，当辅助子PA开启时，主子PA应处于饱和边缘。** 当输入功率水平进一步增加时，两个子功率放大器最终都会饱和。 辅助子PA中使用了更大的晶体管，以提供更高的饱和输出功率。 **主子PA和辅助子PA对总输出功率的贡献取决于输出耦合器的耦合系数。 因此，输出功率回退（OPBO）水平可以通过晶体管的宽度比和输出耦合器的耦合系数来控制。** 与传统的 Doherty PA 相比，这提供了更大的设计灵活性。

子 PA 连接到输入和输出匹配网络，**<font color = salmon>该网络几乎独立于输入功率电平来维持其阻抗匹配</font>**。 在非平衡PA架构中，这些匹配网络是宽带的； 因此，**<font color = salmon>阻抗匹配不会受到晶体管寄生电容随输入功率变化的显着影响。两个子 PA 的输出信号通过输出耦合器组合。 混合耦合器可以使用宽带结构（例如兰格耦合器）来实现，从而形成具有回退效率增强的宽带 PA 架构</font>**。 与使用限带阻抗逆变器的传统 Doherty PA 相比，这两个功能（即使用宽带阻抗匹配网络和 Lange 耦合器）对于改善不平衡 PA 带宽至关重要。

值得注意的是，当两个晶体管工作在 B 类和 C 类模式时，**<font color = DeepSkyBlue >它们的跨导和栅源电容的非线性分别相对于功率电平是压缩的和扩展的，因此可以相互补偿 影响[18]</font>**。 这有助于减轻不平衡 PA 的 AM-PM 失真，这是现代通信中传统使用的复杂调制信号的一个重要特征。 然而，这需要仔细调整晶体管的非线性曲线。

### B.回退效率增强

![image2](https://github.com/WaveDragon/test/assets/78013131/bcb287d1-bda4-4e9a-8ea6-c2e33b8ed2ea)
>用于分析不平衡 PA 的等效电路。 入射和反射电压波分量分别以蓝色和红色显示。 所需的功率流路径由蓝色宽箭头显示。

我们对不平衡 PA 结构进行了详细分析，以展示其运行机制。 定向耦合器可以通过以下散射参数矩阵来描述[19]：

$$ \begin{align*} [S]= \left [{ \begin{array}{cccc} 0 &\quad a&\quad -jb &\quad 0\\ a &\quad 0 &\quad 0 &\quad -jb \\ -jb &\quad 0 &\quad 0 &\quad a\\ 0 &\quad -jb &\quad a &\quad 0\\ \end{array} }\right]\tag{1}\end{align*} $$

其中 a 和 b 与耦合器的耦合系数有关，0 < C < 1，因为 a = C 且 $ b = (1 − C^2)^{1/2}$ 。使用图 2 的电路（输出网络）并假设 主子PA和辅助子PA的输出阻抗与负载阻抗和输出耦合器匹配，即 $ Z_{o,m} = Z_{o,a} = Z_0 = R_L $ ，输出电压导出为

$$ \begin{equation*} V_{\mathrm{ out}} = V_{3}^{-} = S_{31} V_{1}^{+} + S_{34} V_{4}^{+}\tag{2}\end{equation*} $$

从而：

$$ \begin{equation*} V_{\mathrm{ out}} = -j\sqrt {1-C_{o}^{2}} V_{o,m} + C_{o} V_{o,a}.\tag{3}\end{equation*} $$


需要注意的是，由于输入混合耦合器在主放大器和辅助放大器的输入电压之间提供了 90° 的相移，因此它们的输出电压之间也存在 90° 的相位差，即，这些可以被视为 $  V_{o,m} = \lvert V_{o,m} \rvert  $ 和 $ V_{o,a} = −j \lvert V_{o,a} \rvert $ 。

对于较小的输出耦合系数，$ \lvert V_{out} \rvert = \lvert V_{o,m} \rvert $ ，而对于较大的耦合系数，$ \lvert V_{out} \rvert = \lvert V_{o,a} \rvert $ 。 

因此，应选择适中的耦合系数，以实现适当的回退效率提高。 输送到负载的功率 $ P_{out} = {\lvert V_{out}\rvert}^{2}/2R_L $  可使用 (3) 确定为:


$$ \begin{align*} P_{\mathrm{ out}} = \big (1-C_{o}^{2}\big) P_{o,m} + C_{o}^{2} P_{o,a} + 2 C_{o} \sqrt {1-C_{o}^{2}} \sqrt {P_{o,m} P_{o,a}} \\\tag{4}\end{align*} $$

其中 $ P_{o,m} = {\lvert V_{o,m} \lvert} ^{2}/2R_{L} $ 和 $ P_{o,a} = {\lvert V_{o,a}\rvert}^{2}/2R_{L} $ 分别表示主子 PA 和辅助子 PA 的输出功率。

主、辅子PA产生的部分功率被输送到隔离端口。 利用图2（输出网络），可以得到隔离端口的电压为

$$ \begin{equation*} V_{\mathrm{ iso}} = V_{2}^{-} = S_{21} V_{1}^{+} + S_{24} V_{4}^{+}\tag{5}\end{equation*}
$$

从而有：

$$ \begin{equation*} V_{\mathrm{ iso}} = C_{o} V_{o,m} {-} j \sqrt {1-C_{o}^{2}} V_{o,a}.\tag{6}\end{equation*} 
$$

如果主辅子PA的输出电压比可以保持为 $ {\lvert V_{o,a}\rvert} / {\lvert V_{o,m}\rvert} = C_{o}/(1 − C_{o}^{2} )^{1/2} $ ，
则 $ V_{iso} = 0 $，输出功率到隔离端口变为零。 然而，这并不是在 $ V_{o,a} = 0 $ 时实现高效率的必要条件。传送到隔离端口的功率可由下式得出：

$$ \begin{align*} P_{\mathrm{ iso}} = C_{o}^{2} P_{o,m} + \big (1-C_{o}^{2}\big) P_{o,a} - 2 C_{o} \sqrt {1-C_{o}^{2}} \sqrt {P_{o,m} P_{o,a}}. \\\tag{7}\end{align*}
$$

根据功率守恒定律，$P_{out} + P_{iso} = P_{o,m} + P_{o,a}$。事实上，**<font color = salmon>这种四端口输出功率合路器提高了功率放大器的带宽，但由于隔离端口的功率损耗，效率却有所降低。为了提高输出功率合路器的效率，应尽量减小 Piso</font>**。我们将在下文中详细讨论这一问题。两个副 PA 的输出功率和增益相对于输入功率的特性建模如图 3所示。

![image3](https://github.com/WaveDragon/test/assets/78013131/5ce588d2-fb52-4dd9-a0f6-d3c9f70bfb3d)
>子 PA 输出功率和增益与输入功率特性的简化模型。(a) Main sub-PA.(b) Auxiliary sub-PA ($ A = (K_gG_p)^n/(K_pP_{sat})^{n-1} $)

AB 类偏置的主副 PA 由 $G_P$ 的线性功率增益建模，直到饱和为止，其中假定输出功率恒定为 $ P_{sat}$ 。输入饱和功率电平由 $ P_{sat}/G_p $ 给出。辅助副 PA 采用 C 类偏置，输入开启功率电平为 $P_{on,a}$。当输入功率水平低于$P_{on,a}$ 时，输出功率和增益均为零，接通后输出功率和增益逐渐增大。输出功率和增益与输入功率的关系是非线性的，我们将其描述为:



$$
\begin{align*} P_{o,a}=&A (P_{i,a} - P_{on,a})^{n}\tag{8}\\ G_{a}=&A (P_{i,a} - P_{on,a})^{n-1}\tag{9}\end{align*}
$$

其中 n 是偏差和过程相关的参数（通常 1 < n < 2）。 参数A可以如下确定。 我们假设饱和时的输出功率和辅助子PA的功率增益分别由 $ K_{p}P_{sat} $ , $ K_{g}G_{p} $ 给出。 参数 $ K_{p} $ , $ K_{g} $ 定义为：

$$
\begin{align*} K_{p}=&\frac {P_{\mathrm{ sat,a}}}{P_{\mathrm{ sat,m}}}\tag{10}\\ K_{g}=&\frac {G_{p,a}}{G_{p,m}} \tag{11}\end{align*}
$$

>公式横线_左右两端不要留空格

使用(8)–(11)，$ A = (K_{g} G_{p})^{n} / (K_{p} P_{sat})^{n−1} $ . 而辅助子PA的输入饱和功率可导出为 $ P_{on,a} + K_p P_{sat}/K_gG_p $ ，如图3(b)所示。 辅助晶体管 $ W_a $ 的宽度比主晶体管 $ W_m $ 的宽度大 $ K_w $ 倍

$$
\begin{equation*} K_{w} = \frac {W_{a}}{W_{m}}.\tag{12}\end{equation*}
$$

因此，**其线性功率增益和饱和输出功率水平也相对于主晶体管的线性功率增益和饱和输出功率水平成比例**。 饱和功率比 Kp、功率增益比 Kg 和晶体管宽度比 Kw 之间的关系取决于工艺以及工作频率。 **晶体管的输出功率水平大致与其宽度成比例，K p ≈ Kw，而晶体管的增益通常不会成比例地缩放，但往往保持恒定**，甚至由于损耗增加而导致较大器件的增益下降（在本设计中，Kg ≈ 1）。 此外，由于辅助晶体管基于C类，其功率增益可以低于AB类偏置主晶体管的功率增益。 辅助子 PA 可以在主子 PA 饱和之前或之后开启。 我们选择 PA 参数，使得主子 PA 饱和的开始与辅助子 PA 的开启一致，并将 PA 的相关输入功率定义为输入回退功率 $ P_{in,bo} $ 。

使用（4）和（10），峰值功率和回退时的输出功率电平可以导出为

$$
\begin{align*} P_{\mathrm{ out,pp}}=&\big (\sqrt {1-C_{o}^{2}} + \sqrt {K_{p}} C_{o}\big)^{2} P_{\mathrm{ sat}}\tag{13}\\ P_{\mathrm{ out,bo}}=&\big (1-C_{o}^{2}\big)P_{\mathrm{ sat}}\tag{14}\end{align*}
$$

导致 OPBO 水平为

$$
\begin{equation*} {\mathrm{ OPBO}} = 20 \log _{10} \left [{1 + \frac { \sqrt {K_{p}} C_{o}}{\sqrt {1-C_{o}^{2}}} }\right]\!.\tag{15}\end{equation*}
$$

请注意，**<font color = salmon>回退水平取决于晶体管的功率比和输出耦合器的耦合系数 </font>**。 图 4 显示了 OPBO 与参数 $ K_p $ 和 $ C_o $ 的关系。对于 3 dB 耦合器 $ (C_o = 1 / \sqrt{2}) $ ，6 dB 回退要求 $ K_p = 1 $ ，这与 Doherty PA 中的相同 。 对于较低的耦合系数，例如 −4.8 dB $ (C_o = 1 / \sqrt{3}) $，晶体管的功率比应该更大 $ K_p = 2 $。 我们将在本文中比较非平衡 PA 和 Doherty PA 的特性。 此时，我们注意到，在不平衡 PA 中，回退电平可以通过两个参数来控制，而在 Doherty PA 中只能通过晶体管宽度比来调整。 如果我们假设辅助晶体管的宽度是主晶体管的两倍且 $ K_p = K_w = 2 $ ，则 Doherty PA 的回退电平可得出： OPBO = 20log10(1 + $ K_p $ ) = 9.5 dB，而在非平衡 PA 中，它可以在很宽的范围内控制，如式（15）和图 4 所示。

![image4](https://github.com/WaveDragon/test/assets/78013131/dae2e24c-a1b9-4233-a0a3-dd7a7502d8d3)
>OPBO电平与晶体管功率比Kp和输出耦合器Co的耦合系数的关系 

如前所述，**输出功率合成器由于隔离端口中的功率损耗而具有不完美的效率**。 我们推导出组合器的效率，并研究输出耦合器的耦合系数对其性能的影响。 组合器的效率由下式给出

$$
\begin{equation*} \eta _{\mathrm{ comb}} = \frac {P_{\mathrm{ out}}}{P_{\mathrm{ out}}+P_{\mathrm{ iso}}} = \frac {P_{\mathrm{ out}}}{P_{o,m}+P_{o,a}}.\tag{16}\end{equation*}
$$

通过(4)可以表达为：

$$
\begin{equation*} \eta _{\mathrm{ comb}} = \frac {\big (\sqrt {1-C_{o}^{2}} + C_{o} \sqrt {P_{o,a}/P_{o,m}}\,\big)^{2} }{1+P_{o,a}/P_{o,m}}\tag{17}\end{equation*}
$$

它是 $ C_o $ 和功率比 $ p_{o,a}/P_{o,m} $ 的函数。 在图 5 中，显示了不同 $ C_o $ 值的组合器效率与归一化输出功率的关系。 

> 行内希腊字母下标使用方式： \eta_{comb,bo} = 1 − C_{o}^{2}

在回退状态中， $ \eta_{comb,bo} = 1 − C_{o}^{2} $ ； 

因此，为了提高效率，优选使用较低的耦合系数。 在峰值功率下，$ P_{o,a}/P_{o,m} = K_p $，其中对于给定的 OPBO，$ K_p $ 是从 (15) 导出的。 耦合系数较低时，合路器效率 $ \eta_{comb,pp} $ 会降低。 在回退功率和峰值功率之间存在一个功率水平，此时组合器效率变为100 。 这是传送到隔离端口的功率为零的点，根据 (7)，可得出 $ P_{o,a} / P_{o,m} = C_{o}^{2} / (1-C_{o}^{2}) $。 可以看出，这种情况发生在归一化输出功率电平 $ −OPBO − 20 \log_{10}(1 − C_{o}^{2} ) $ 处，例如，OPBO = 6dB以及Co =−8dB 时，在 −4.5 dB 回退电平处。

![image5](https://github.com/WaveDragon/test/assets/78013131/b7d583a7-a2ce-4ce9-aaf4-31a30c38bfc0)

>对于输出组合器的不同耦合系数，输出组合器效率与归一化输出功率的关系。 (a) 6dB OPBO。 (b) 9dB OPBO。



施加到 PA 的输入功率在主子 PA 和辅助子 PA 之间分配。 使用图2所示的电路（输入网络），假设子PA的输入阻抗与输入耦合器和输入源阻抗匹配，即 $ Z_{i,m} = Z_{i,a } = Z_0 = R_S $，则可以被证明

$$
\begin{align*} V_{i,m}=&V_{2}^{-} = S_{21} V_{1}^{+} = C_{i} V_{\mathrm{ in}}\tag{18}\\ V_{i,a}=&V_{3}^{-} = S_{31} V_{1}^{+} = -j \sqrt {1-C_{i}^{2}}V_{\mathrm{ in}}\tag{19}\end{align*}
$$

其中 $ C_i $ 是输入混合耦合器的耦合系数。 传送到主子 PA 和辅助子 PA 的输入功率由下式给出:

$$
\begin{align*} P_{i,m}=&C_{i}^{2} P_{\mathrm{ in}}\tag{20}\\ P_{i,a}=&\big (1-C_{i}^{2}\big) P_{\mathrm{ in}}.\tag{21}\end{align*}
$$

因此，主辅子PA的输出功率根据输入功率得出如下：

$$
\begin{align*} P_{o,m}=&\begin{cases} G_{p} C_{i}^{2}P_{\mathrm{ in}} & P_{\mathrm{ in}} < P_{\mathrm{ in,bo}}\\ P_{\mathrm{ sat}} & P_{\mathrm{ in}} \geq P_{\mathrm{ in,bo}}\\ \end{cases}\tag{22}\\ P_{o,a}=&\begin{cases} 0 & P_{\mathrm{ in}} < P_{\mathrm{ in,bo}}\\ A \big (1-C_{i}^{2}\big)^{n}(P_{\mathrm{ in}}-P_{\mathrm{ in,bo}})^{n} & P_{\mathrm{ in,bo}}\leq P_{\mathrm{ in}} < P_{\mathrm{ in,pp}}\\ P_{\mathrm{ sat,a}} & P_{\mathrm{ in}} \geq P_{\mathrm{ in,pp}}\\ \end{cases} \\\tag{23}\end{align*}
$$

其中 $ P_{in,bo} $ 和 $ P_{in,pp} $ 分别是回退和峰值功率时的输入功率电平，由下式给出

$$
\begin{align*} P_{\mathrm{ in,bo}}=&\frac {1}{C_{i}^{2}}\frac {P_{\mathrm{ sat}}}{G_{p}} = \frac {P_{on,a}}{1-C_{i}^{2}}\tag{24}\\ P_{\mathrm{ in,pp}}=&\left [{\frac {1}{C_{i}^{2}}+\frac {K_{p}}{K_{g}}\frac {1}{1-C_{i}^{2}}}\right] \frac {P_{\mathrm{ sat}}}{G_{p}}.\tag{25}\end{align*}
$$

使用(24)，可以得出辅助子PA所需的开启功率电平。 不平衡 PA 的输入输出功率特性可以使用 (4)、(22) 和 (23) 得出。

$$
\begin{align*} \eta = \frac {\big (1-C_{o}^{2}\big) P_{o,m} + C_{o}^{2} P_{o,a} + 2 C_{o} \sqrt {1-C_{o}^{2}}\sqrt {P_{o,m}P_{o,a}}}{\frac {1}{\eta _{m}} P_{o,m} + \frac {1}{\eta _{a}} P_{o,a}} \\\tag{26}\end{align*}
$$

其中 $ \eta_{m} $ 和 $ \eta_{a} $ 分别表示主子 PA 和辅助子 PA 的效率。 使用 (22)、(23) 和 (26)，回退和峰值功率时的效率由下式给出:

$$
\begin{align*} \eta _{\mathrm{ bo}}=&\big (1-C_{o}^{2}\big) \eta _{m}\tag{27}\\ \eta _{\mathrm{ pp}}=&\frac {\big (\sqrt {1-C_{o}^{2}} + \sqrt {K_{p}} C_{o}\big)^{2}}{\frac {1}{\eta _{m}} + \frac {K_{p}}{\eta _{a}} }.\tag{28}\end{align*}
$$

值得注意的是，回退和峰值功率时的效率可能不同。 利用(15)、(27)、(28)可以证明:

$$
\begin{equation*} \frac {\eta _{\mathrm{ bo}}}{\eta _{\mathrm{ pp}}} = \left [{ 1+ K_{p} \frac {\eta _{m}}{\eta _{a}} }\right] 10^{-{\mathrm{ OPBO}}/20}\tag{29}\end{equation*}
$$

对于 $ K_p > (10^{OPBO/20} − 1) \eta _a / \eta _m $ 来说大于 1。对于 6-dB 回退电平和  $\eta _m = \eta _a $  可以满足 $ K_p $ > 1 ，即 $ C_o $ < 1/√2。 因此，优选较小的输出耦合系数以实现较高的回退效率。

在峰值功率和回退以外的输出功率水平下，效率 (26) 通过 $ P_{o,m} $ 、$ P_{o,a} $ 、$ \eta _m $ 和 $ \eta _a $ 与功率相关。 为了获得输入功率的 $ \eta _m $ 和 $ \eta _a $ ，我们首先注意到饱和状态下短沟道晶体管的漏极电流由下式给出

$$
\begin{equation*} I_{D} \approx k_{0} W (V_{\mathrm{ GS}} - V_{T})\tag{30}\end{equation*}
$$

其中 k0 是与工艺相关的参数，W 是晶体管的宽度，VGS 是栅源电压，VT 表示增强（耗尽）模式晶体管的阈值（夹断）电压 [20]。 我们假设 RF 信号的形式为

$$
\begin{equation*} V_{\mathrm{ GS}}(t) = V_{\mathrm{ GS0}} + V_{\mathrm{ RF}} \cos (\omega _{0} t)\tag{31}\end{equation*}
$$

应用于晶体管。 漏极电流波形取决于偏置模式。 如果晶体管在 B 类模式下偏置，即 $ V_{GS0} = V_T $ （如主 subPA 的预期），则产生的漏极电流是峰值为 $ k_{0} WV_{RF} $ 的半波正弦曲线。 该波形的直流分量和基波分量 $ I_{D0} $ 和 $ I_{D1} $ 均与 $ V_{RF} $ 成正比。 结果，直流和射频功率分量变化为 $ P_{dc}  = V_{DD}I_{D0} \propto V_{RF} $ 和 $ P_{RF} \propto  R_{opt} I_{D1}^{2} \propto V_{RF}^{2} $ ，导致 $ \eta = P_{RF}/P_{dc} \propto V_{RF} $ 。 对于匹配的晶体管，$ P_{in} \propto \sqrt{P_{in}} $ ； 因此，$ \eta  \propto \sqrt{P_in} $ 。 因此，主子PA的效率可以表示为

$$
\begin{align*} \eta _{m} = \begin{cases} \eta _{m,{\mathrm{ max}}}\displaystyle \sqrt {\frac {P_{\mathrm{ in}}}{P_{\mathrm{ in,bo}}}}& P_{\mathrm{ in}} < P_{\mathrm{ in,bo}}\\ \eta _{m,{\mathrm{ max}}} & P_{\mathrm{ in}} \geq P_{\mathrm{ in,bo}}\\ \end{cases}\tag{32}\end{align*}
$$

其中 $ \eta _{m,max} $ 表示饱和时的最大效率，例如，B 类模式下 $ \eta _{m,max} = \pi /4 = 78.5 % $ 。



如果晶体管在 C 类模式下偏置，即 $ V_{GS0} $ < $ V_T $ ，如辅助子 PA 预期的那样，则应考虑不同的情况。 电流波形的导通角 $ \alpha $ 由式(30)和式(31)导出：

$$
\begin{equation*} \alpha = 2 \cos ^{-1} \left [{\frac {V_{T} - V_{\mathrm{ GS0}} }{V_{\mathrm{ RF}}} }\right]\tag{33}\end{equation*}
$$

这取决于射频电压幅度。 传统上，导通角被定义为最大射频电压，这会导致 PA 饱和。 可以看出，电流波形分量 $ I_{D0} $ 和 $ I_{D1} $ 导出为:

$$
\begin{align*} I_{D0} (\alpha)=&\frac {k_{0}WV_{\mathrm{ RF}}}{2\pi } \frac {2\sin \left ({\frac {\alpha }{2}}\right) - \alpha \cos \left ({\frac {\alpha }{2}}\right)}{1-\cos \left ({\frac {\alpha }{2}}\right)}\tag{34}\\ I_{D1} (\alpha)=&\frac {k_{0}WV_{\mathrm{ RF}}}{2\pi } \frac {\alpha - \sin (\alpha)}{1-\cos \left ({\frac {\alpha }{2}}\right)}.\tag{35}\end{align*}
$$

直流功率由 $ P_{dc} = V_{DD}I_{D0}( \alpha ) $ 给出，而射频功率由 
$ P_{\mathrm{RF}}=(1 / 2) R_{\mathrm{opt}}(\alpha) I_{D 1}^{2}(\alpha) \approx(1 / 2)\left[V_{\mathrm{DD}} / I_{D 1, \max }(\alpha)\right] I_{D 1}^{2}(\alpha) $ 
其中 $ I_{D 1, \max} $ 表示最大 RF 电压 $ V_{RF,max} $ 处的基波漏极电流分量。 因此，使用（34）和（35），效率可以表示为:

$$
\begin{equation*} \eta _{a} (\alpha) \approx \frac {1}{2} \frac {I_{D1} ^{2}(\alpha)}{I_{D1,{\mathrm{ max}}} (\alpha)I_{D0} (\alpha)} = \eta _{a,{\mathrm{ max}}} (\alpha) \frac {V_{\mathrm{ RF}}}{V_{\rm RF,{\mathrm{ max}}}}\tag{36}\end{equation*}
$$

其中  $ \eta _{a,{\mathrm{ max}}} (\alpha) $ C 类 PA 饱和时的最大效率

$$
\begin{equation*} \eta _{a,{\mathrm{ max}}} (\alpha) = \frac {1}{4} \frac {\alpha - \sin (\alpha)}{\sin \left ({\frac {\alpha }{2}}\right) - \frac {\alpha }{2} \cos \left ({\frac {\alpha }{2}}\right)}.\tag{37}\end{equation*}
$$

参数 $ V_{\mathrm{RF}} / V_{\mathrm{RF} \text {,max }} $ 可以使用 $ V_{RF} \propto \sqrt{P_{in}}  $ 与输入功率相关。并注意辅助子 PA 在 $ P_{in,bo} $ 处开启并在 $ P_{in,pp} $ 处达到饱和。因此，辅助子PA的效率可以表示为

$$
\begin{align*} \eta _{a}= \begin{cases} 0 & P_{\mathrm{ in}} < P_{\mathrm{ in,bo}}\\ \eta _{a,{\mathrm{ max}}}\displaystyle \sqrt {\frac {P_{\mathrm{ in}} - P_{\mathrm{ in,bo}}}{P_{\mathrm{ in,pp}} - P_{\mathrm{ in,bo}}}} & P_{\mathrm{ in,bo}} \leq P_{\mathrm{ in}} < P_{\mathrm{ in,pp}}\\ \eta _{a,{\mathrm{ max}}} & P_{\mathrm{ in}} \geq P_{\mathrm{ in,pp}}\\ \end{cases}\tag{38}\end{align*}
$$

其中 $ \eta _{a,max} $ 由(37)给出

不平衡 PA (26) 的总效率可以根据输出功率得出，如图 6 所示。 假设主子 PA 和辅助子 PA 的最大效率分别为 ηm,max=78.5% (B类)和ηa,max=85.5%（C类，导通角α=0.8π），而输入耦合器的耦合系数为Ci=−3dB。 值得注意的是，通过降低输出耦合器Co的耦合系数，回退效率ηbo提高，但代价是峰值功率效率ηpp降低。 对于小 Co ， ηbo→ηm ，如 (27) 所预期的那样。 也有可能实现类似 Doherty 的行为，例如，对于 Co≈−6 dB，但对于具有大 PAPR 的调制信号，首选更高的回退效率，其中它们的概率密度函数 (pdf) 主要集中在 后退。

![image6](https://github.com/WaveDragon/test/assets/78013131/1d275e77-a2c4-431e-8209-eedec138e8eb)
>不平衡 PA 的效率与标准化输出功率的关系。 (a) 6dB OPBO。 (b) 9dB OPBO。 主子PA和辅助子PA的最大效率分别为ηm,max=78.5%（B级）和ηa,max=85.5%（C级，导通角α=0.8π）。 假设Ci=-3dB并且n=1.5。

不平衡 PA 的增益可以使用为输出组合器 (4)、输入分配器 (20) 和 (21) 以及子 PA (22) 和 (23) 开发的模型得出。 特别是，使用 (13)、(14)、(24) 和 (25) 可以得出输出回退和峰值功率处的增益：

$$
\begin{align*} G_{\mathrm{ bo}}=&C_{i}^{2} \big (1-C_{o}^{2}\big) G_{p}\tag{39}\\ G_{\mathrm{ pp}}=&\frac {\big (\sqrt {1-C_{o}^{2}} + \sqrt {K_{p}} C_{o}\big)^{2}}{\frac {1}{C_{i}^{2}}+\frac {K_{p}}{K_{g}}\frac {1}{1-C_{i}^{2}} } G_{p}.\tag{40}\end{align*}
$$

图 7 显示了不平衡 PA 的增益与输出功率的关系。 假设主子PA和辅助子PA的增益分别为 $ G_p = 10 $ 和 $ G_{p,a} = K_{g}G_{p} $ ，其中Kg≈1和Kp根据OPBO和Co使用(15)确定。 此外，在模拟中考虑Ci=-3dB。

![image7](https://github.com/WaveDragon/test/assets/78013131/966a6cea-de19-40b5-aa47-6033aa620b07)
>不平衡 PA 的增益与标准化输出功率的关系。 (a) 6dB OPBO。 (b) 9dB OPBO。 主子PA和辅助子PA的增益分别为 $ G_p = 10 $ 和 $ K_g G_p = 10 $ 。 假设Ci=-3dB并且n=1.5。

输入耦合器的耦合系数对不平衡PA的效率和增益的影响如图8所示。效率受Ci的影响很小，而较大的Ci有助于实现更高的增益。 此外，值得注意的是，对于一些Ci值，例如-5dB < Ci <-4dB，回退范围内的增益变化可以被最小化。 这减少了 PA 的 AM-AM 失真，这对于高 PAPR 调制信号尤其重要。 我们可以设置 Ci 来实现 $ G_{bo} = G_{pp} $ ，使用 (39)、(40) 和 (4)，结果为

$$
\begin{equation*} C_{i} = \left [{ \frac {10^{\mathrm{ OPBO/10}}-1}{10^{\mathrm{ OPBO/10}}-1+K_{p}/K_{g}} }\right]^{1/2}.\tag{41}\end{equation*}
$$

对于OPBO=6dB、Co=-8dB、Kg=1，最佳Ci导出为Ci=-4.4dB。 应该注意的是，在回退到峰值功率范围内仍然存在一些增益变化，这取决于两个子 PA 的非线性分布，例如参数 n ，但通常很小

![image8](https://github.com/WaveDragon/test/assets/78013131/077f9fd2-680e-4731-94fe-284a10d5d993)

>输入耦合器耦合系数对不平衡 PA 效率和增益的影响。 (a)效率。 (b) 增益。 假设OPBO=6dB，Co=-8dB，并且n=1.5。


根据主子 PA 和辅助子 PA 的输入功率要求确定 Ci 时还有另一个重要考虑因素。 在饱和状态下使用 (20) 和 (21)，Ci 可以导出为

$$
\begin{equation*} C_{i} = \frac {1}{\sqrt {1+P_{i,a}/P_{i,m}}} = \frac {1}{\sqrt {1 + K_{p}/K_{g}}}.\tag{42}\end{equation*}
$$

对于OPBO=6dB、Co=-8dB并且Kg=1，这导致Ci=-8.0dB。 到目前为止，我们讨论了根据增益、增益变化和输入功率驱动要求设置 Ci 的三个标准。 如果子 PA 实现为单级放大器，则应根据输入功率驱动要求选择 Ci，以确保不平衡 PA 的正常运行。 然而，在子 PA 使用多级放大器的情况下，可以设置 Ci 来最小化增益变化，同时驱动级满足增益要求。

最后一点是辅助子PA的非线性模型参数n对不平衡PA性能的影响。 在图 9 中，显示了 1≤n≤2 时的效率和功率增益与输出回退的关系。 n 越大，回退到峰值功率范围内的效率会稍高，而回退和峰值功率处的效率与该参数无关。 此外，在 n 的适中值下实现了最小增益变化。

![image9](https://github.com/WaveDragon/test/assets/78013131/8badcdc3-7028-4af4-9a92-970095ad9acc)
>C 类辅助子 PA 非线性参数 n（以 $ P_{o,a} = A(P_{i,a} − P_{on,a})^{n} $ 表示）对不平衡 PA 的效率和增益的影响。 (a)效率。 (b) 增益。 假设 OPBO=6 dB、Co=−8 dB 和 Ci=−3 dB。

### C.线性操作

我们根据子 PA 的散射参数和混合耦合器的耦合系数推导出不平衡 PA 的小信号散射参数。 为了简化分析，假设子PA是单边的，即 $ S_{12} = 0 $ 。 使用图10 和 (1) 所示的电路，可得出入射电压波 $ V_{1}^{+} $ 和 $ V_{2}^{+} $ 为

$$
\begin{align*} V_{1}^{+}=&C_{i} V_{\mathrm{ in}}^{+}\tag{43}\\ V_{2}^{+}=&-j\sqrt {1-C_{i}^{2}}V_{\mathrm{ in}}^{+}.\tag{44}\end{align*}
$$

由于假设放大器是单边的，因此其输入端口处的反射电压波由下式给出

$$
\begin{align*} V_{1}^{-}=&S_{11,m}V_{1}^{+}\tag{45}\\ V_{2}^{-}=&S_{11,a}V_{2}^{+}.\tag{46}\end{align*}
$$

因此，输入反射波可导出为

$$
\begin{equation*} V_{\mathrm{ in}}^{-} = C_{i} V_{1}^{-} - j\sqrt {1-C_{i}^{2}} V_{2}^{-}.\tag{47}\end{equation*}
$$

不平衡 PA 的输入反射系数可使用 (43)–(47) 和 
$ S_{11,UPA} = V_{in}^{-} / V_{in}^{+} $ 得出：

$$
\begin{equation*} S_{11,{\mathrm{ UPA}}} = C_{i}^{2} S_{11,m} - \big (1-C_{i}^{2}\big) S_{11,a}.\tag{48}\end{equation*}
$$

类似地，可以得出输出反射系数为

$$
\begin{equation*} S_{22,{\mathrm{ UPA}}} = -\big (1- C_{o}^{2}\big)S_{22,m} + C_{o}^{2} S_{22,a}.\tag{49}\end{equation*}
$$

因此，输出电压波形可推导为

$$
\begin{align*} V_{3}^{-}=&S_{21,m}V_{1}^{+}\tag{50}\\ V_{4}^{-}=&S_{21,a}V_{2}^{+}.\tag{51}\end{align*}
$$

使用(43)、(44)和(50)-(52)，不平衡PA增益: $ S_{21UPA} = V_{out} / V_{in}^{+} $ 推导如下：

$$
\begin{equation*} S_{21,{\mathrm{ UPA}}} = -j\big [C_{i}\sqrt {1-C_{o}^{2}}S_{21,m}+ C_{o}\sqrt {1-C_{i}^{2}}S_{21,a}\big].\tag{53}\end{equation*}
$$

![image10](https://github.com/WaveDragon/test/assets/78013131/42c1de29-2476-48f1-a4a0-6b8818cb6f9d)
>用于导出不平衡 PA 的散射参数的电路。

如果两个子 PA 的设计使得 $ S_{11,m} = S_{11,a} $ 且 $ S_{22,m} =  S_{22,a} $ ，则 (48) 和 (49) 简化为

$$
\begin{align*} S_{11,{\mathrm{ UPA}}}=&-\big (1-2C_{i}^{2}\big) S_{11,{\mathrm{ PA}}}\tag{54}\\ S_{22,{\mathrm{ UPA}}}=&-\big (1- 2 C_{o}^{2}\big)S_{22,{\mathrm{ PA}}}\tag{55}\end{align*}
$$

表明不平衡 PA 的输入和输出反射系数比组成子 PA 的输入和输出反射系数小 $\lvert 1-2 C_{i}^{2}\rvert \text { and }\lvert 1-2 C_{o}^{2}\rvert $ 分别。 值得注意的是，非平衡PA仍然部分继承了传统平衡PA的阻抗匹配改善特性。 此功能简化了子 PA 的输出和输入匹配网络的设计。 此外，这降低了 PA 对负载（例如天线）阻抗变化的敏感性，这是 5G 应用中的一个重要挑战。 在具有相同子 PA 和 3 dB 耦合器的平衡 PA 的情况下，即 $ C_i = C_o = 1 / \sqrt{2} $，这些结果简化为 $ S_{11,UPA} = S_{22,UPA} = 0 $ 以及，$ S_{21,UPA} = −jS_{21,PA} $ ， 正如预期的那样[19]。

### D.带宽考虑

由于使用宽带兰格耦合器而不是窄带阻抗逆变器进行负载调制，因此与 Doherty PA 相比，不平衡 PA 可以提供更宽的带宽。 我们详细阐述了非平衡 PA 的带宽注意事项，以阐明其相对于 Doherty PA 的优势。 兰格耦合器可以提供宽带宽，例如全倍频程，具体取决于其布局结构和实现过程。 它们的耦合系数和相位响应偏离频带边缘的目标值，导致不平衡 PA 的性能下降（将在第 III-A 节中进一步讨论）。**兰格耦合器的带宽通常远高于非平衡 PA 的其他子电路的带宽。 由于阻抗逆变器的高阻抗变换比，Doherty PA 在回退时的带宽有限** [3]。 为了对非平衡 PA 和 Doherty PA 进行简单比较，我们假设非平衡 PA 的输出匹配网络是使用 λ/4 传输线实现的。 在图 11 所示的电路中，传输线的特性阻抗选择为 6 dB OPBO 电平。 两种架构中传输线的阻抗变换比如图 11（c）所示。 在回退时的Doherty PA中，传输线TL1和TL2的阻抗变换比分别为4和 $ R_{opt} / 2R_{L} $ ； 因此，带宽往往会受到 TL1 的显着限制。 在不平衡 PA 中，在回退功率和峰值功率下，阻抗变换比由 $ R_{opt} / R_{L} $ 和 $ R_{opt} / K_{w}R_{L} $ 给出（请注意，$ W_a = K_w W_m $；因此，$ R_{opt,a} = R_{opt} / K_{w} $ ），其中 TL1 主要是 退避时很重要。 对于典型电路参数，$ R_{opt} / R_{L} $ 通常低于 4，这表明不平衡 PA 在回退时提供更宽带宽的潜力。

子 PA 的输出匹配网络应将负载电阻 RL 转换为晶体管 $ R_{opt,m} $ 和 $ R{opt,a} $ 的最佳电阻，同时吸收晶体管 $ C{out,m} $ 和 $ C_{out,a} $ 的输出寄生电容。 这些匹配网络的带宽取决于其阻抗变换比 $ R_{opt,m} / R_L $ 和 $ R_{opt,a} / R_L $ 以及

最佳负载阻抗的品质因数 $ Q_{L,m} = \omega_{c}R_{opt,m}C_{out,m} $ 和 $ Q_{L,a} = \omega_cR_{opt,a}C_{out,a} $ 

（ωc 是频带中心）[21]。 应该注意的是，通过使用更高阶的匹配网络可以进一步扩展带宽，而这对于Doherty PA中的阻抗逆变器来说是不可能的。 然而，输出匹配网络的带宽和插入损耗之间存在权衡，具体取决于其电路结构和无源元件的品质因数，这转化为不平衡 PA 的效率带宽权衡。

此外，在不平衡PA中，呈现给主子PA的阻抗与辅助子PA的输出阻抗无关。 这是正交耦合器的基本特征，可以解释如下。 利用式(1)，对于 $ V_{1}^{+} $ 的入射电压波，当端口2和端口3匹配时，即 $ V_{2}^{+} = V_{3}^{+} = 0 $，$ V_{1}^{-} = 0 $； 

因此，$ \Gamma_{in} = V_{1}^{+} / V_{1}^{-} = 0 $ 。因此，端口 1 的匹配也与端口 4 终端阻抗无关。 然而，在 Doherty PA 中，该阻抗受到辅助 PA 输出阻抗的影响，辅助 PA 的输出阻抗从峰值功率变化到回退，并且还随频率变化。 这使得不平衡 PA 的带宽比 Doherty PA 有了额外的改善。


![image11](https://github.com/WaveDragon/test/assets/78013131/9ebf10a3-b086-46ef-9fc7-899d28cbf9a6)
>Doherty 和非平衡 PA 的宽带性能比较。 (a) Doherty PA 架构。 (b) 不平衡的 PA 架构。 (c) 两种架构中传输线在回退（BO）和峰值功率（PP）下的阻抗变换比。 在此比较中，假设不平衡 PA 的输出匹配网络是使用 λ/4 传输线实现的。


## PA电路设计

我们现在展示宽带完全集成的非平衡 PA 原型的设计，在 4.5-6.5-GHz 带宽下具有 6 dB 回退的峰值效率。 该 PA 采用 250 nm GaN-on-SiC 工艺实现。 与其他工艺相比，功率GaN晶体管具有较大的最佳负载电阻和相对较小的寄生电容，因此被广泛用于各种宽带放大器架构的实现中[22]-[30]。 电路原理图如图12所示。下面介绍了所开发的理论的应用和电路设计中的实际考虑。

![image12](https://github.com/WaveDragon/test/assets/78013131/5d9c9e37-4e20-4d1e-9786-de5bc0eab097)
>实施的不平衡 PA 示意图。

### A. 输出和输入所使用Lange耦合器

输出和输入耦合器使用曲折兰格耦合器实现，以实现宽带性能并节省芯片面积[见图13(a)]。 输出耦合器的耦合系数根据 6dB OPBO 要求（见图 4）和效率与输出功率曲线（见图 6）确定。 本设计中选择 ≈−8 dB 的耦合系数，以最大限度地提高回退效率。 更强的耦合系数，例如-6 dB，可以提供更线性的增益，如图7（a）所示，但回退效率较低[ $ \eta_{bo} = (1-C_{o}^2) \eta_m $ ]。 然而，在此设计中，优选较低的耦合系数，以展示不平衡 PA 架构的回退效率增强功能。 此外，如图8(b)所示，可以选择输入耦合器的耦合系数，使得主子PA的压缩增益可以用辅助子PA的扩展增益来补偿，以实现 线性增益。

兰格耦合器布局结构，即传输线的宽度、间距和长度，通过广泛的电磁仿真进行了优化。 输出耦合器的最终性能如图 13(b) 所示。 两个输出端口的传输系数在 5.5 GHz 时分别为 -7.9 dB (=Co) 和 -1.2 dB。 在 4.0–7.0 GHz 范围内，幅度不平衡 $ \Delta A  $ 和相位差与 -90° 的偏差 $ \Delta \Phi $ 分别为 0.6–1.3 dB 和 3.2°–6.3°。 平均插损定义为 $ IL = −10 log10({\lvert S_{21} \rvert }^2 + {\lvert S_{31} \rvert }^2)  $ ，为0.3~0.5 dB，三个端口的反射系数为  $ \lvert Sii  \rvert < −27 dB  $ 。

![image13](https://github.com/WaveDragon/test/assets/78013131/5cc26e7e-c6f3-4fc6-9751-e8e8330e8c2c)

>曲折兰格耦合器的物理结构和模拟性能。 (a) 物理结构。 (b) 输出耦合器。 (c) 输入耦合器。 物理尺寸（包括金属宽度、间距和总长度 {w , s , l } ）对于输出耦合器为 {10, 40, 5400} μm，对于输入耦合器为 {10, 20, 5500} μm。 两个耦合器的平均插入损耗均为 0.3–0.5 dB，三个端口的反射系数在 4.0–7.0 GHz 范围内为 $ \lvert Sii  \rvert < −27 dB  $。


主辅子PA之间的隔离度是非平衡PA中的一个重要参数。 在图 14 中，模拟隔离，即 $ \lvert S_{14}  \rvert < −27 dB  $ 显示了兰格耦合器的输出与频率的关系。 在 4.0–7.0 GHz 范围内的隔离度读数 <−29.7 dB，这证实了主晶体管的阻抗与辅助子 PA 的输出阻抗无关。


![image14](https://github.com/WaveDragon/test/assets/78013131/04cd2922-f197-4ca4-9cff-a3279239bb27)
>仿真中主功放和辅助功放的隔离度


### B. 主功放和辅助功放的子功放(Sub-PAs)

主子 PA 和辅助子 PA 中晶体管的宽度可以根据不平衡 PA 的输出功率目标以及第 III-A 节中导出的耦合器的耦合系数来确定。 根据所需的峰值输出功率  $ P_{out,pp}  $ 和 OPBO 电平，回退输出功率由 $ P_{out,bo} = P_{out,pp} − OPBO $ 给出。 使用式（14）和主子 PA 输出匹配网络的估计损耗 $ L_{omn,m} $ ，主晶体管所需的输出功率可导出为 $ P_{tr,m} = P_{out,bo} − 10 log_{10}(1 − C_{o}^{2} ) + L_{omn,m} $ . 这可用于负载牵引模拟来导出主晶体管 $ W_{m} $ 的宽度。 在此设计中，为了实现 36dBm 峰值输出功率和 6dB OPBO，$ C_{o} = −8dB $ 并假设 $ L_{omn,m} \approx -1 dB $ ，主晶体管所需的功率为 31.8 dBm。 使用 4 × 125 $ \mu $ m 的晶体管宽度即可满足这一要求。

此外，借助图4，通过第III-A节中选择的 $ C_{o} $，获得参数 $ K_{p} $ ，导致辅助晶体管的宽度为 $ W_{a} \approx K_{p}W_{m}  $ 。 实际上，**<font color = salmon>较大的晶体管具有较高的损耗</font>**（例如，由于较大的寄生电阻），因此效率较低，这会降低不平衡 PA 的效率。 此外，该晶体管较大的寄生电容限制了 PA 带宽。 因此，辅助晶体管的最佳宽度应小于理论值。 在此设计中，8 × 125 $ \mu m $ 的晶体管宽度可实现最佳效率和带宽性能。 此选择将 OPBO 移动到大约 5 dB。

主、辅子 PA 的输出匹配网络应提供最佳负载电阻 $ R_{opt,m} \approx 150 \Omega $ 和 $ R_{opt,a} \approx  70 \Omega $ 在基频频段。 在本设计中，我们实现了输出匹配网络，使子 PA 能够以连续模式运行。 通过在基波和二次谐波频带中提供最佳负载阻抗，可以提高宽带宽内的 PA 效率 [24]。 该网络使用堆叠金属微带传输线和金属-绝缘体-金属 (MIM) 电容器来实现。

使用与其栅极串联的阻容网络（即主晶体管的 $ R_{1}  $ 和  $ C_{4} $ ，辅助晶体管的 $ R_{2,3} $ 和 $ C_{10} $ ）来确保晶体管的稳定性。 **<font color = salmon>电阻器降低了晶体管的低频增益，该增益可能非常高并导致不稳定，而电容器在工作频带中旁路电阻器以避免不必要的增益损失</font>**。 稳定性系数 $ \mu $ 用于评估晶体管的稳定性[19]。 **此外，栅极和漏极偏置焊盘在内部使用大型片上电容器进行旁路，在外部则通过多个并联板载电容器进行旁路** 。

仿真结果表明，主子 PA 在 22 dBm 输入功率和 5.5 GHz 下提供 32 dBm 输出功率、56% 效率和 10 dB 功率增益。 对于辅助子 PA，输入功率为 26 dBm 时，这些值分别为 36 dBm、49% 和 10 dB。 非平衡 PA 的峰值输出功率为 34 dBm，峰值功率时效率为 35%，回退大约 5dB时效率为 41%。 在 4.5–6.5 GHz 范围内，峰值功率时的效率为 27%–38%，回退时的效率为 28%–42%。 在图15中，示出了主子PA、辅助子PA和不平衡PA的模拟S11和S22。 值得注意的是，与子 PA 相比，不平衡 PA 结构改善了输入和输出回波损耗。 在图 16 中，显示了 4.5-6.5 GHz 范围内的模拟 AM-PM 失真。 由于主晶体管的压缩非线性与辅助晶体管的扩展非线性进行了适当的补偿，因此在靠近频带中心（例如 5.5-6.0 GHz）时实现了较低的 AM-PM。

![image15](https://github.com/WaveDragon/test/assets/78013131/77cf3b3d-1daf-4361-ad88-f0dbb677d2a8)
>仿真所得主功放辅助功放以及不平衡放大器 $ S_{11} S_{22} $

![image16](https://github.com/WaveDragon/test/assets/78013131/86b9b3c1-f30c-418c-92f2-bd33d149bcd7)
>.5-6.5 GHz 范围内的模拟 AM-PM 失真

## 测试结果

PA 芯片采用 WIN Semiconductors 的 250 nm GaN-on-SiC 工艺制造。 该芯片如图 17 所示，其中使用蜿蜒的兰格耦合器来节省芯片面积。 晶体管的漏极偏置为 28 V，而栅极偏置选择为 -2.3 和 -4.0 V，以实现高回退效率。 芯片通过引线键合到测试 PCB，并使用散热器来提高测量中的热稳定性。

![image17](https://github.com/WaveDragon/test/assets/78013131/94b03feb-052d-453f-9be4-c02a4f8744f2)
>芯片版图

### A. 连续波测量

PA 的输出功率、效率和增益与频率的关系如图 18 所示。结果是在 24 dBm 输入功率下获得的。 这相当于大约 1-3 dB 增益压缩。 值得注意的是，与仿真结果相比，测量的频率响应存在向上偏移。 小信号增益的 3dB 带宽为 4.3–6.5 GHz (41.6%)。 在 4.5–6.5 GHz 范围内，效率读数为 28%–39%。

![image18](https://github.com/WaveDragon/test/assets/78013131/af239a15-63a0-49f3-ba01-0f0b274c91fb)
>测量和仿真的输出功率、DE 和增益（大信号和小信号，LS/SS）与 24 dBm 输入功率下频率的关系。

图 19 显示了 5.0 GHz 下测量和仿真的增益、DE 和 PAE 与输出功率的关系。值得注意的是，效率与输出功率的形状遵循不平衡 PA 的理论特性，即最大效率为 在退避时实现。 在峰值功率/回退时获得 34%/40% 的 DE，而 PAE 为 25%/35%。 
图 20 显示了 4.5–6.5 GHz 范围内测得的 DE、PAE 和增益与输出功率的关系。PA 提供 32.2–34.3 dBm 输出功率，峰值功率时 DE 为 27%–37%，DE 为 27%–40% 5-6dB 回退。 该 PA 原型是作为所开发的不平衡 PA 架构的证明。 通过优化 PA 电路可以进一步提高性能。

![image19](https://github.com/WaveDragon/test/assets/78013131/2667b3cd-124a-411b-89ad-35bdb619bcd7)
>测量和仿真的增益、DE 和 PAE 与 5.0 GHz 下输出功率的关系。


![image20](https://github.com/WaveDragon/test/assets/78013131/b415b807-4e4b-4b86-b0ed-c0819944d45d)
>Measured DE, PAE, and gain versus output power across 4.5–6.5 GHz.


### B. 调制信号测量

PA 操作使用具有高达 200 MHz 调制带宽 ($ BW_{m} $) 和 7.2 dB PAPR 的 256-QAM 信号进行评估。 调制信号使用 MATLAB 代码生成，加载到 R&S SMW200A 矢量信号发生器中，然后应用于 PA。 使用 R&S FSW45 矢量信号分析仪捕获输出信号，并在 MATLAB 中进行处理以提取输出信号特征。

测得的 AM-AM 和 AM-PM 失真特性如图 21 所示。使用数字预失真 (DPD) 可以显着减轻这两种失真。 输出信号星座如图 22 所示，其中当 $ BW_{m} $ = 100 MHz 时，平均输出功率为 25.5 dBm 时，均方根误差矢量幅度 ( $ EVM_{rms} $ ) 为 3.7% (−28.6 dB)。 当 $ BW_{m} $ = 200 MHz 时，$ EVM_{rms} $ 增加至 4.5% (−26.9 dB)。 使用 DPD，两种情况下的 $ EVM_{rms} $ 可以分别改善至 0.53% (−45.5 dB) 和 0.65% (−43.7 dB)。 测量的信号频谱如图 23 所示，其中 $ BW_{m} $ = 100 MHz 时的相邻信道泄漏比 (ACLR) 在没有 DPD 的较低/较高信道上为 -34.1/−34.1 dBc，并改善至 -45.7/−46.4 dBc 应用 DPD 后。 对于 $ BW_{m} $ = 200 MHz，无 DPD 时 ACLR 为 −32.5/−33.0 dBc，有 DPD 时 ACLR 为 −42.1/−44.1 dBc。

![image21](https://github.com/WaveDragon/test/assets/78013131/7301ee0f-1ec8-406d-820d-c4bf47c94cb7)
>在使用和不使用 DPD 的情况下，在 25.5 dBm 平均输出功率下测量的 AM-AM 和 AM-PM 失真特性。 结果是使用具有 100 MHz 带宽和 7.2 dB PAPR 的 5.0 GHz、256-QAM 信号获得的。

![image22](https://github.com/WaveDragon/test/assets/78013131/8a941418-0b61-46d6-afde-fd23514d84aa)
>在 25.5dBm 平均输出功率下测得的输出星座。 结果是使用具有 100-/200-MHz 带宽和 7.2-dB PAPR 的 5.0-GHz、256-QAM 信号获得的。

![image23](https://github.com/WaveDragon/test/assets/78013131/d7eb1afa-8a65-4b12-9360-c4b28a8d2bad)
>测得的 256-QAM 信号的输出频谱，带宽为 100/200 MHz，PAPR 为 7.2 dB。

在图 24 中，显示了测量的 EVM 和 ACLR（下部通道和上部通道的平均值）。 在 DPD 的帮助下，在 18-28-dBm 平均输出功率范围和整个 4.5-6.5-GHz 频段，EVM 和 ACLR 可以分别提高到 <1% 和 <−39 dBc。 

![image24](https://github.com/WaveDragon/test/assets/78013131/a2e3675e-6964-4239-bd71-60bc034fb995)
>测量的 EVM 和 ACLR（较低通道和较高通道的平均值）与具有 100 MHz 带宽和 7.2 dB PAPR 的 256-QAM 信号的平均输出功率。 通过 DPD ON/OFF 扫描整个载波频率。

图 25 展示了调制带宽对线性性能的影响。显示了测量的 EVM 和 ACLR 与 $ BW_{m} $ = 100/200 MHz 时的平均输出功率。 线性度随着调制带宽的增加而降低，但仍然可以获得良好的性能。 图 26 显示了平均漏极效率与平均输出功率的关系。 在平均输出功率为 25.5dBm 时，效率达到 30%，并且几乎与调制带宽无关。 通过以更高的输出功率运行 PA 并使用 DPD 补偿增加的非线性，可以实现更高的效率。

![image25](https://github.com/WaveDragon/test/assets/78013131/eb1d8cb4-7201-4790-8468-cd00ad481c48)
>测量的 EVM 和 ACLR（较低通道和较高通道的平均值）与具有 100/200 MHz 带宽和 7.2 dB PAPR 的 256-QAM 信号的平均输出功率。 通过 DPD 打开/关闭扫描整个调制带宽。

![image26](https://github.com/WaveDragon/test/assets/78013131/01bab1fd-55ac-410c-96c7-756fdb4d18c5)
>测得的平均漏极效率与 PAPR 为 7.2dB 的 256-QAM 信号的平均输出功率。

在表 I 中，所实施的不平衡 PA 的性能与之前具有回退效率增强功能的完全集成 GaN PA（所有这些都是 Doherty PA）进行了比较。 实现了宽操作带宽 (37%)。 这是所提出的 PA 架构的主要特征，并且是使用宽带兰格耦合器和阻抗匹配网络而不是阻抗逆变器的结果。 使用宽带 100-/200-MHz 256-QAM 信号评估的线性度导致 $ EVM_{rms} $ ≈−28.6/−26.9 dB，无需任何预失真。 在保持最先进性能的同时，实现了创纪录的 200 MHz 调制带宽（8 S × 200 MHz = 1.6 GS/s 数据速率）。 这是由于在 B 类和 C 类模式下运行的主子 PA 和辅助子 PA 的压缩和扩展非线性行为消除了上述非线性。

![Table1](https://github.com/WaveDragon/test/assets/78013131/841b3c64-dfa0-4ead-8975-5c069d5210ab)
>具有回退效率增强功能的宽带全集成 GaN PA 的比较

## 结论
在本文中，我们提出了一种用于增强宽带回退效率的非平衡 PA 架构。 PA采用两个子PA和Lange耦合器作为输入功率分配器和输出功率分配器。 结果表明，该 PA 的 OPBO 电平由晶体管宽度比和输出兰格耦合器的耦合系数控制。 该 PA 架构可以实现宽带操作，这是由于使用子 PA 的宽带输出和输入阻抗匹配网络以及具有固有宽带响应的兰格耦合器。 与使用限带阻抗逆变器的传统 Doherty PA 相比，这两个功能对于改善不平衡 PA 带宽至关重要。 完全集成的 PA 概念验证采用 250 nm GaN-on-SiC 工艺实现，并在 6 GHz 以下频段实现了创纪录的 200 MHz 调制带宽（1.6 GS/s 数据速率）。

[论文地址](https://ieeexplore.ieee.org/document/9173563)























