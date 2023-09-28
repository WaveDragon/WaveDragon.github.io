---
title: Unbalanced Power Amplifier An Architecture for Broadband Back-Off Efficiency Enhancement
author: WaveDragon
date: 2023-9-28 11:11:00 +0800
categories: [Blogging, RadioFrequency]
tags: [Study]
math: true
mermaid: true
# image:
#   path: /commons/devices-mockup.png
#   width: 800
#   height: 500
#   alt: Responsive rendering of Chirpy theme on multiple devices.
---

## 摘要
摘要：在本文中，我们提出了一种新的宽带功率放大器 (PA) 架构，具有回退效率增强功能，支持非常宽的调制带宽。 非平衡 PA 由两个协作的子 PA 组成，使用兰格耦合器作为输入功率分配器和输出功率组合器。 PA 操作由晶体管的宽度比和兰格耦合器的耦合系数控制。**输出功率回退（OPBO）水平由晶体管的宽度比和输出耦合器的耦合系数给出，而最大效率在回退点实现。** 与传统的 Doherty PA 相比，这些功能提供了更大的设计灵活性，其中 OPBO 只能通过晶体管的宽度比来设置，并且在峰值功率下实现最大效率。 使用**宽带谐波匹配网络，主子 PA 和辅助子 PA 以连续模式运行，以提高宽带宽上的效率**。 采用 250 nm GaN-on-SiC 工艺实现的完全集成非平衡 PA 可实现 32.2–34.3 dBm 输出功率，峰值功率时效率为 27%–37%，5–6 dB 时效率为 27%–40% 回退，跨 4.5–6.5 GHz。 该 PA 为具有 100-/200-MHz 带宽、7.2-dB PAPR 和 25.5- 的 256-QAM 信号提供 3.7/4.5% (−28.6/−26.9 dB) rms 误差矢量幅度 (EVMrms) 和 30% 平均效率。 dBm 平均输出功率，不使用任何预失真。

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
用于分析不平衡 PA 的等效电路。 入射和反射电压波分量分别以蓝色和红色显示。 所需的功率流路径由蓝色宽箭头显示。

我们对不平衡 PA 结构进行了详细分析，以展示其运行机制。 定向耦合器可以通过以下散射参数矩阵来描述[19]：

$$ \begin{align*} [S]= \left [{ \begin{array}{cccc} 0 &\quad a&\quad -jb &\quad 0\\ a &\quad 0 &\quad 0 &\quad -jb \\ -jb &\quad 0 &\quad 0 &\quad a\\ 0 &\quad -jb &\quad a &\quad 0\\ \end{array} }\right]\tag{1}\end{align*} $$

其中 a 和 b 与耦合器的耦合系数有关，0 < C < 1，因为 a = C 且 $ b = (1 − C^2)^{1/2}$ 。使用图 2 的电路（输出网络）并假设 主子PA和辅助子PA的输出阻抗与负载阻抗和输出耦合器匹配，即 $ Z_{o,m} = Z_{o,a} = Z_0 = R_L $ ，输出电压导出为

$$ \begin{equation*} V_{\mathrm{ out}} = V_{3}^{-} = S_{31} V_{1}^{+} + S_{34} V_{4}^{+}\tag{2}\end{equation*} $$

从而：

$$ \begin{equation*} V_{\mathrm{ out}} = -j\sqrt {1-C_{o}^{2}} V_{o,m} + C_{o} V_{o,a}.\tag{3}\end{equation*} $$


需要注意的是，由于输入混合耦合器在主放大器和辅助放大器的输入电压之间提供了 90° 的相移，因此它们的输出电压之间也存在 90° 的相位差，即，这些可以被视为 $ V_{o,m} = |V_{o,m}| $ 和 $ V_{o,a} = −j |V_{o,a}| $ 。

对于较小的输出耦合系数，$ |V_{out}| =  |V_{o,m}| $ ，而对于较大的耦合系数，$|V_{out}|       = |V_{o,a}|$ 。 

因此，应选择适中的耦合系数，以实现适当的回退效率提高。 输送到负载的功率 $ P_{out} = |V_{out}|^2/2R_L $  可使用 (3) 确定为:


$$ \begin{align*} P_{\mathrm{ out}} = \big (1-C_{o}^{2}\big) P_{o,m} + C_{o}^{2} P_{o,a} + 2 C_{o} \sqrt {1-C_{o}^{2}} \sqrt {P_{o,m} P_{o,a}} \\\tag{4}\end{align*} $$

其中 $ P_{o,m} = |V_{o,m}|^2/2R_L $ 和 $ P_{o,a} = |V_{o,a}|^2/2R_L $ 分别表示主子 PA 和辅助子 PA 的输出功率。

主、辅子PA产生的部分功率被输送到隔离端口。 利用图2（输出网络），可以得到隔离端口的电压为

$$ \begin{equation*} V_{\mathrm{ iso}} = V_{2}^{-} = S_{21} V_{1}^{+} + S_{24} V_{4}^{+}\tag{5}\end{equation*}
$$

从而有：

$$ \begin{equation*} V_{\mathrm{ iso}} = C_{o} V_{o,m} {-} j \sqrt {1-C_{o}^{2}} V_{o,a}.\tag{6}\end{equation*} 
$$

如果主辅子PA的输出电压比可以保持为 $ |V_{o,a}|/|V_{o,m}| = C_o/(1 − C^2_o )^{1/2} $ ，则 $V_{iso} = 0 $，输出功率到隔离端口变为零。 然而，这并不是在 $V_{o,a} = 0$ 时实现高效率的必要条件。传送到隔离端口的功率可由下式得出：

$$ \begin{align*} P_{\mathrm{ iso}} = C_{o}^{2} P_{o,m} + \big (1-C_{o}^{2}\big) P_{o,a} - 2 C_{o} \sqrt {1-C_{o}^{2}} \sqrt {P_{o,m} P_{o,a}}. \\\tag{7}\end{align*}
$$

根据功率守恒定律，$P_{out} + P_{iso} = P_{o,m} + P_{o,a}$。事实上，**<font color = salmon>这种四端口输出功率合路器提高了功率放大器的带宽，但由于隔离端口的功率损耗，效率却有所降低。为了提高输出功率合路器的效率，应尽量减小 Piso</font>**。我们将在下文中详细讨论这一问题。两个副 PA 的输出功率和增益相对于输入功率的特性建模如图 3所示。

![image3](https://github.com/WaveDragon/test/assets/78013131/5ce588d2-fb52-4dd9-a0f6-d3c9f70bfb3d)
子 PA 输出功率和增益与输入功率特性的简化模型。(a) Main sub-PA.(b) Auxiliary sub-PA ($ A = (K_gG_p)^n/(K_pP_{sat})^{n-1} $)

AB 类偏置的主副 PA 由 $G_P$ 的线性功率增益建模，直到饱和为止，其中假定输出功率恒定为 $ P_{sat}$ 。输入饱和功率电平由 $ P_{sat}/G_p $ 给出。辅助副 PA 采用 C 类偏置，输入开启功率电平为 $P_{on,a}$。当输入功率水平低于$P_{on,a}$ 时，输出功率和增益均为零，接通后输出功率和增益逐渐增大。输出功率和增益与输入功率的关系是非线性的，我们将其描述为:

需要注意的是，由于输入混合耦合器在主放大器和辅助放大器的输入电压之间提供了 90° 的相移，因此它们的输出电压之间也存在 90° 的相位差，即，这些可以被视为 $ V_{o,m} = |V_{o,m}| $ 和 $ V_{o,a} = −j |V_{o,a}| $ 。

$$
\begin{align*} P_{o,a}=&A (P_{i,a} - P_{on,a})^{n}\tag{8}\\ G_{a}=&A (P_{i,a} - P_{on,a})^{n-1}\tag{9}\end{align*}
$$

其中 n 是偏差和过程相关的参数（通常 1 < n < 2）。 参数A可以如下确定。 我们假设饱和时的输出功率和辅助子PA的功率增益分别由 $ K _p P_{sat} $ 和 $ K_g G_ p $ 给出。 参数 $K _p$  和 $ K_g $ 定义为：

$$
\begin{align*} K_{p}=&\frac {P_{\mathrm{ sat,a}}}{P_{\mathrm{ sat,m}}}\tag{10}\\ K_{g}=&\frac {G_{p,a}}{G_{p,m}}.\tag{11}\end{align*}
$$

使用(8)–(11)，$A = (K_g G_ p)^n/(K _p P_{sat})^{n−1}$ ，而辅助子PA的输入饱和功率可导出为 $ P_{on,a} + K_p P_{sat}/K_gG_p $ ，如图3(b)所示。 辅助晶体管 $ W_a $ 的宽度比主晶体管 $ W_m $ 的宽度大 $ K_w $ 倍

### 待用图片


![image4](https://github.com/WaveDragon/test/assets/78013131/dae2e24c-a1b9-4233-a0a3-dd7a7502d8d3)

![image5](https://github.com/WaveDragon/test/assets/78013131/b7d583a7-a2ce-4ce9-aaf4-31a30c38bfc0)

![image6](https://github.com/WaveDragon/test/assets/78013131/1d275e77-a2c4-431e-8209-eedec138e8eb)

![image7](https://github.com/WaveDragon/test/assets/78013131/966a6cea-de19-40b5-aa47-6033aa620b07)

![image8](https://github.com/WaveDragon/test/assets/78013131/077f9fd2-680e-4731-94fe-284a10d5d993)

![image9](https://github.com/WaveDragon/test/assets/78013131/8badcdc3-7028-4af4-9a92-970095ad9acc)

![image10](https://github.com/WaveDragon/test/assets/78013131/42c1de29-2476-48f1-a4a0-6b8818cb6f9d)

![image11](https://github.com/WaveDragon/test/assets/78013131/9ebf10a3-b086-46ef-9fc7-899d28cbf9a6)

![image12](https://github.com/WaveDragon/test/assets/78013131/5d9c9e37-4e20-4d1e-9786-de5bc0eab097)


![image13](https://github.com/WaveDragon/test/assets/78013131/5cc26e7e-c6f3-4fc6-9751-e8e8330e8c2c)

![image14](https://github.com/WaveDragon/test/assets/78013131/04cd2922-f197-4ca4-9cff-a3279239bb27)

![image15](https://github.com/WaveDragon/test/assets/78013131/77cf3b3d-1daf-4361-ad88-f0dbb677d2a8)

![image16](https://github.com/WaveDragon/test/assets/78013131/86b9b3c1-f30c-418c-92f2-bd33d149bcd7)

![image17](https://github.com/WaveDragon/test/assets/78013131/94b03feb-052d-453f-9be4-c02a4f8744f2)

![image18](https://github.com/WaveDragon/test/assets/78013131/af239a15-63a0-49f3-ba01-0f0b274c91fb)

![image19](https://github.com/WaveDragon/test/assets/78013131/2667b3cd-124a-411b-89ad-35bdb619bcd7)

![image20](https://github.com/WaveDragon/test/assets/78013131/b415b807-4e4b-4b86-b0ed-c0819944d45d)

![image21](https://github.com/WaveDragon/test/assets/78013131/7301ee0f-1ec8-406d-820d-c4bf47c94cb7)

![image22](https://github.com/WaveDragon/test/assets/78013131/8a941418-0b61-46d6-afde-fd23514d84aa)

![image23](https://github.com/WaveDragon/test/assets/78013131/d7eb1afa-8a65-4b12-9360-c4b28a8d2bad)

![image24](https://github.com/WaveDragon/test/assets/78013131/a2e3675e-6964-4239-bd71-60bc034fb995)

![image25](https://github.com/WaveDragon/test/assets/78013131/eb1d8cb4-7201-4790-8468-cd00ad481c48)

![image26](https://github.com/WaveDragon/test/assets/78013131/01bab1fd-55ac-410c-96c7-756fdb4d18c5)