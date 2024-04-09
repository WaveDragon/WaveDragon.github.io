---
title: A GaN MMIC Load-Modulated Balanced Amplifier With Modified Output Coupler for Efficiency Enhancement Over a Larger Power Back-Off Range
author: WaveDragon
date: 2024-04-09 11:11:00 +0800
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

# 具有改进的输出耦合器的 GaN MMIC 负载调制平衡放大器，可在更大的功率回退范围内提高效率

## 摘要

本文首先介绍了一种采用 0.15um GaN 工艺开发的单片微波集成电路 (MMIC) 负载调制平衡放大器 (LMBA)。 在此简介中，非对称输出耦合器用于在更大的 OBO 范围内进一步增强输出功率和输出回退 (OBO) 效率。 这种MMIC LMBA工作模式依赖于三路有源负载调制过程，通过修改输出耦合器的耦合系数，可以提供更多的设计参数和自由度。 
为了在毫米波 (mm-wave) 下验证所提出的 LMBA，演示、制造并测试了 24.7-25.7 GHz MMIC LMBA。 测量结果表明，该 MMIC LMBA 可以提供 35.2dBm 的饱和输出功率，峰值漏极效率为 37.7%。 在 6dB/8dB/10dB OBO 下，可分别获得 23.8-30%、24.2-27% 和 20-24% 的功率附加效率 (PAE)。 测得的 S21 为 15 dB，增益变化为 ±0.4 dB。 当由 PAPR 为 9.2dB 的 100MHz 64-QAM OFDM 调制信号驱动时，通过 DPD 测量的 ACPR 提高至 –45.04 dBc。 在这种情况下，PA 的平均效率为 25.2%，平均输出功率为 26.2dBm。

## 一、介绍

大频谱资源可用性的无线需求导致微米波（mm-wave）频段在第五代（5G）无线通信中受到广泛的关注[^1]。 同时，具有高峰均功率比（PAPR）的调制信号得到普及，以实现最大频谱效率[^2]。 因此，考虑到PA在射频系统中的主导地位，需要在大输出功率回退（OBO）范围内具有高效率[^3]。

Doherty PA (DPA)  [^4]、[^5]、[^6] 和 **<font color = salmon>负载调制平衡放大器 (LMBA)</font>**  [^7]、[^8]、[^9]、[^10]、[^11]、[^12]、 [^13]，凭借其高输出功率回退效率，引起了人们的广泛关注。 然而，随着回退水平的增加，DPA 负载调制网络的设计变得非常复杂，因为它涉及多段传输线。 

相比之下，这种 LMBA 已被证明是一种可靠的方法，可以通过简单的负载调制网络在深层 OBO 级别上保持比 DPA 更高的效率。 **其架构通过输出耦合器结合了三级放大器，其中包括一个控制放大器（CA）和两个平衡放大器（BA），导致负载调制行为，从而提高回退效率。** 传统的 LMBA 只能提供 6 dB OBO 电平，并且 BA 均作为载波放大器偏置在 AB 类模式 [^7]、[^8]。 为了通过扩展回退范围来提高效率，[^9] 和 [^10] 中提出了伪 Doherty LMBA (PD-LMBA) 和顺序 LMBA (SLMBA)，将 CA 设置为载波，将 BA 设置为峰值放大器。 **然而，CA 负载阻抗保持恒定值，导致线性度恶化，并严重降低 OBO 范围中间的效率**。 在[^11]中，混合非对称LMBA（H-AMBA）可以在更大的回退范围内实现类似于**三级Doherty PA的三峰值效率**。 由于不同的BA为了方便而采用了相同的晶体管，导致功率利用率不足，导致功率成本。 为了充分利用所有单元的功率，[^12]中提出了一种用于 LMBA 的**不对称输出耦合器**。 需要注意的是，隔离端口处BA产生的残余功率会被消耗，从而导致整体PA的饱和效率下降。 虽然这些不同类型的LMBA已逐渐应用于6 GHz以下应用，但由于严格的设计规则检查（DRC）和晶体管高频性能的限制，在毫米波频段实现LMBA架构是一个巨大的挑战 。 由于工艺和对称输出耦合器的限制，[^13]中报道的毫米波Doherty-Like LMBA只能提供较低的OBO电平（6dB）和较小的输出功率。

为了解决上述缺点，本文采用商用 0.15um GaN 工艺设计和制造了带有改进输出耦合器的毫米波 LMBA。 为了进一步提高输出功率和回退效率，提出了一种不对称输出耦合器，使得所提出的LMBA可以在更大的OBO范围内实现效率提高。 与报道的LMBA[^13]相比，我们提出的LMBA表现出更高的OBO效率和输出功率。

## 二、提出的MMIC LMBA 理论和分析

### A.基于改进正交耦合器的负载调制过程

![image1](https://github.com/WaveDragon/test/assets/78013131/6661e3c7-b5e4-4389-8161-5fcca8ad9a46)
LMBA 的等效框图（建议的 LMBA，C0 $ \ne $ 0.707（3dB）,传统的 LMBA，C0 = 0.707（3dB））。

如图1所示，该LMBA架构由平衡放大器（BA）（PA1和PA2）和控制放大器（CA）组成，它们被视为三个理想的压控电流源。 然后，它们通过两个对称定向耦合器进行耦合，其耦合系数在输入和输出功率处设置为 3dB (C0=0.707)。 简而言之，无论PA1和PA2电流是否相等，CA都可以通过修改耦合系数来实现连续负载调制。 因此，对理想正交耦合器的S、Z矩阵进行分析是非常有必要的，其可以表示为[^13]:

$$
\begin{align*} \left [{ S }\right]=&\begin{bmatrix} 0 &\quad - ja &\quad - b &\quad 0 \\ - ja &\quad 0 &\quad 0 &\quad - b \\ - b &\quad 0 &\quad 0 &\quad - ja \\ 0 &\quad - b &\quad - ja &\quad 0 \\ \end{bmatrix} \tag{1}\\ \left [{ Z }\right]=&\left ({\left [{ U }\right] + \left [{ S }\right] }\right)\left ({\left [{ U }\right] - \left [{ S }\right] }\right)^{- 1} \tag{2}\end{align*}
$$

其中a和b与定向耦合器的耦合系数 $ (C_{0}) $有关。$ [U] $ 是单位矩阵。 对于无损耦合器，需要保证 $ 0 < C_{0} < 1 $ ，同时满足 $ b=C_{0} $ 和 $ a = {(1 − C^{2}_{0})}^{1/2} $ 。 那么，输出耦合器的电流和电压之间的关系可以表示为

$$
\begin{align*} \begin{bmatrix} V_{c} \\ V_{b2} \\ V_{b1} \\ V_{L} \\ \end{bmatrix} = Z_{0}\begin{bmatrix} 0 &\quad - jk_{1} &\quad 0 &\quad jk_{2} \\ - jk_{1} &\quad 0 &\quad jk_{2} &\quad 0 \\ 0 &\quad jk_{2} &\quad 0 &\quad - jk_{1} \\ jk_{2} &\quad 0 &\quad - jk_{1} &\quad 0 \\ \end{bmatrix}\begin{bmatrix} jI_{c}e^{{j{\theta }}} \\ \quad - jI_{b2} \\ I_{b1} \\ - V_{L}/R_{L} \\ \end{bmatrix} \tag{3}\end{align*}
$$

其中 $ V_{c} $、$ V_{b2} $ 、$ V_{b1} $ 和 $ V_{L} $ 分别代表负载CA、PA2、PA1和ZL的参考电压。 电流 $ I_{1} $ 向耦合器的隔离端口注入幅度为 $ I_{C} $ 、相位可调的信号 $ \theta $ ，以控制负载调制过程。 PA1、PA2和CA的阻抗 $ Z_{b1} $、$ Z_{b2} $ 和 $ Z_{c} $ 可以计算为 :

$$
\begin{align*} Z_{b1}=&Z_{0}\left ({k_{1}^{2} - {}\frac {k_{2}I_{b2}}{I_{b1}} + {}\frac {k_{1}k_{2}I_{c}e^{{j{\theta }}}}{I_{b1}}}\right) \tag{4}\\ Z_{b2}=&Z_{0}\left ({{}\frac {k_{2}I_{b1}}{I_{b2}} + {}\frac {k_{1}I_{c}e^{{j{\theta }}}}{I_{b2}}}\right) \tag{5}\\ Z_{c}=&Z_{0}\left ({k_{2}^{2} - \frac {k_{1}(I_{b2} - k_{2}I_{b1})}{I_{c}e^{{j{\theta }}}}}\right) \tag{6}\end{align*}
$$

其中 $ k_{1} = 1/{(1−b^2)}^{1/2} $ 且 $ k_{2} = b /a $ 由 (1)–​(3) 定义。 非常有趣的是，即使电流 $ I_{b1} $ 等于 $ I_{b2}(I_{b1} = I_{b2})  $ ，CA阻抗也会被调制，而与耦合系数 $ C_{0}.(k_2 \ne 1) $ 的变化无关。 为了简化上述表达式，设置电流比 $ I_{b1max}＝ \gamma_1I_{cmax} $ 和 $ I_{b2max}＝ \gamma_2I_{cmax} $ 。

在本简介中，CA 用作 B 类条件下的载波放大器偏置，而 PA1 和 PA2 均在 C 类模式下工作，具有不同的阈值，作为两个峰值放大器。 在输出回退 (OBO) 级别，CA 仅在 PA1 和 PA2 关闭时工作（即 $ I_{b1} = I_{b2} = 0 $ ）。 在饱和水平，三个放大器达到饱和功率。 假设归一化输入驱动电压电平为 $ \beta $ ，并且 $ \beta _{1} $ 和 $ \beta _{2} $ 是两个输入功率回退电平，分别代表所提出的LMBA的第一和第二峰值效率点。 在低功率和高功率水平下，载波的基波电流 $ I_{c} $ 可以简单地表示为[10]:

$$
\begin{align*} I_{c} = \begin{cases} \beta I_{c\max }\cos \theta,&\quad 0 \leq \beta \leq \beta _{1},\\ \frac {2v_{C}}{Z_{c}(\beta)}\cos \theta,&\quad \beta _{1} \leq \beta \leq 1, - \frac {\pi }{2} \leq \theta < \\ 0, &\quad otherwise \\ \end{cases}\frac {\pi }{2} \tag{7}\end{align*}
$$

其中 $ I_{cmax} $ 是允许流过CA晶体管的最大电流，$ v_{c} $ 表示CA饱和电压。 当 $ \beta < \beta_{1} $ 时，电流 $  I_{c}  $ 呈线性，电压逐渐达到饱和。 当 $ \beta _{1} < \beta < 1 $ 时，过驱动电流会导致严重的非线性。 $ I_{c} $ 的直流分量和基波分量可以通过傅立叶展开式给出。

$$
\begin{align*} I_{c}[{ 0}]=&\frac {2\beta }{\pi \beta _{1}}I_{c\max } \tag{8}\\ I_{c}[{ 1}]=&\frac {\beta }{2\beta _{1}}I_{c\max } \tag{9}\end{align*}
$$

基于理想的 C 类模式，BA 电流 $ I_{b1} $ 和  $ I_{b2} $  可以导出为
$$
\begin{align*} I_{b1} = \begin{cases} 0,&\quad 0 \leq \beta \leq \beta _{1}\\ \frac {\beta \cos \theta - \beta _{1}}{1 - \beta _{1}}I_{b1max},&\quad \beta _{1} \leq \beta \leq 1\\ \end{cases} \tag{10}\\ I_{b2} = \begin{cases} 0,&\quad 0 \leq \beta \leq \beta _{2}\\ \frac {\beta \cos \theta - \beta _{2}}{1 - \beta _{2}}I_{b2max}, &\quad \beta _{2} \leq \beta \leq 1 \\ \end{cases} \tag{11}\end{align*}
$$

其中  $ \theta = arccos (\beta/\beta _{1}) $  由[^10]定义。 $ I_{b1max} $  和  $ I_{b2max} $  是允许流过 PA1 和 PA2 晶体管的最大电流。 根据 (10) 和 (11)，PA1 和 PA2 的直流分量和基波分量可由下式给出:

$$
\begin{align*} I_{bn}[{ 0}]=&\frac {\gamma _{n}I_{c\max }}{1 - \beta _{n}}\frac {2\beta \sin \theta - 2\beta _{n}\theta }{\pi } \tag{12}\\ I_{bn}[{ 1}]=&\frac {\gamma _{n}I_{c\max }}{1 - \beta _{n}}\frac {\beta (2\theta + sin2\theta) - 4\beta _{n}\sin \theta }{2\pi },n = 1,2. \tag{13}\end{align*}
$$

随着输入电平 $ \beta $ 从0增加到1，LMBA的负载调制过程可以分为三种情况进行分析。 

1. 情况1：当0<β≤β1时，所提出的LMBA工作在较低功率区域。
在这种情况下，CA 开启，而 PA1 和 PA2 均完全关闭。 当β=β1时，CA电压才饱和，由式(7)可得 $ v_{c}=\beta_{1}I_{cmax}Z_{c} $ 。 此时，得到电流 $ I_{c}＝\beta I_{cmax} $ 的关系。 同时，三个放大器的负载阻抗由下式给出:

$$
\begin{equation*} Z_{c} = k_{2}^{2}Z_{0}, Z_{b1} = Z_{b2} = \infty.\tag{14}\end{equation*}
$$

2. 情况2：当 $ \beta _{1} \le \beta \le \beta _{2} $  时，所提出的LMBA在Doherty区域运行。 在这种情况下，CA 和 PA2 开启，PA1 关闭。 同时，负载阻抗 $ Z_{c} $ 条件并没有保持在 $ Z_{0} $ ，并且这也正在经历动态负载调制。 随着 $ \beta $ 继续增加到 $ \beta _{2} $ 以上，CA电流Ic增加到最大 $ I_{cmax} $ ，并且PA2电流 $ I_{b2} $ 可由式(13)定义。 因此，三个放大器的负载阻抗可以表示为

$$
\begin{equation*} Z_{c} = {}\frac {k_{2}^{2}v_{c}Z_{0}}{v_{c} + k_{1}I_{b2}Z_{0}}, Z_{b1} = \infty, Z_{b2} = Z_{0}\left ({{}\frac {k_{1}^{2}}{k_{2}} + {}\frac {k_{1}v_{c}}{k_{2}^{2}I_{b2}}}\right)\tag{15}\end{equation*}
$$

3. Case3：当 $ \beta _{2} \le \beta \le 1 $ 时，所提议的LMBA在ALMBA区域中运行。 在这种情况下，CA、PA1 和 PA2 开启。 当 $ \beta = 1 $ 时， $ I_{b1} $ 和 $ I_{b2} $ 增加最大电流 $ I_{b1max} $ 和 $ I_{b2max} $ 。 PA1和PA2功率达到饱和状态。 在此区域，CA、PA1和PA2的负载阻抗可以表示为


$$
\begin{align*} Z_{c}=&{}\frac {k_{2}^{2}v_{c}Z_{0}}{v_{c} + k_{1}(I_{b2} - k_{2}I_{b1})Z_{0}}, Z_{b1} = {}\frac {k_{1}v_{c} + (k_{1}^{2} - k_{2})I_{b2}Z_{0}}{k_{2}I_{b1}} \\ Z_{b2}=&Z_{0}{}\frac {k_{1}^{2}}{k_{2}} + {}\frac {k_{1}v_{c} - k_{2}^{2}I_{b1}Z_{0}}{k_{2}^{2}I_{b2}}\tag{16}\end{align*}
$$

此时，注意到PA2电流 $ I_{b2} $ 急剧增大，可由式(11)求得。 因此，OBO 和饱和水平处的阻抗可以使用 (4)–(6) 重写

$$
\begin{align*} Z_{c,{OBO}}=&\frac {C_{0}^{2}}{1 - C_{0}^{2}}Z_{0} \tag{17}\\ Z_{c,{Sat}}=&\frac {C_{0}^{4}\beta _{1}Z_{0}}{C_{0}^{2}(1 - C_{0}^{2})\beta _{1} + (1 - C_{0}^{2})^{3/2}\gamma _{2} - C_{0}(1 - C_{0}^{2})\gamma _{1})} \qquad \tag{18}\\ Z_{b1,{Sat}}=&Z_{0}\left ({{}\frac {C_{0}^{2}\beta _{1} + ((1 - C_{0}^{2})^{1/2} - C_{0}(1 - C_{0}^{2}))\gamma _{2}}{C_{0}(1 - C_{0}^{2})\gamma _{1}}}\right)\tag{19}\\ Z_{b2,{Sat}}=&Z_{0}\left ({{}\frac {1}{C_{0}(1 - C_{0}^{2})^{1/2}} + {}\frac {(1 - C_{0}^{2})^{- 1/2}\beta _{1} - \gamma _{1}}{\gamma _{2}}}\right) \tag{20}\end{align*}
$$

OBO 可以表示为 [10]：

$$
\begin{align*} OBO=&10\log 10\left ({\frac {P_{c,{Sat}} + P_{b1,{Sat}} + P_{b2,{Sat}}}{P_{c,{OBO}}}}\right) \tag{21}\\ P_{c,{OBO}}=&\frac {1}{2}(\beta _{1}I_{c\max })^{2}Z_{c,{OBO}} \tag{22}\\ P_{c,{Sat}}=&\frac {1}{2}\left ({\frac {v_{c}}{Z_{c,{Sat}}}}\right)^{2}Z_{c,{Sat}} = \frac {1}{2}\left ({\frac {\beta _{1}I_{c\max }Z_{c,{OBO}}}{Z_{c,{Sat}}}}\right)^{2}Z_{c,{Sat}} \qquad \tag{23}\\ P_{b1,{Sat}}=&\frac {1}{2}(I_{b1}^{2}[{ 1}])Z_{b1,{Sat}},P_{b2,{Sat}} = \frac {1}{2}(I_{b2}^{2}[{ 1}])Z_{b2,{Sat}} \tag{24}\end{align*}
$$

其中  $ P_{c,Sat} $ 、 $ P_{b1,Sat} $  和  $ P_{b2,Sat} $  是三个放大器（CA、PA1 和 PA2）的饱和输出功率。 根据式（7）~（15），当 $ \beta _{1} $ 和  $ \beta _{2} $ 确定后，OBO、 $ C_{0} $ 、 $ \gamma _{1} $ 和 $ \gamma _{2} $ 之间的关系如图2所示。从图2中可以看出，不同的OBO电平（6-12dB）为 当β1=0.4和0.5时，分别随耦合系数C0和电流比γ1、γ2变化。 在γ2为0.6至3.8的范围内以及相应的C0为0.37至0.84的范围内，当β1=0.5时可以实现10dB的OBO水平。 当输出耦合器的耦合系数设置为3dB（C0=0.707）时，10dB OBO电平需要γ1=1和γ2=1.96。 在这种情况下，所提出的技术退化为[^12]中提出的H-ALMBA，并且它可以实现由电流Ib1和Ib2之间的差确定的载波PA的动态负载调制。 但此时 PA1 和 PA2 的饱和输出功率 Pb1,Sat 和 Pb2,Sat (Pb1,Sat =Pb2,Sat) 在隔离端口上不能相互抵消。 因此，为了提高输出功率，需要修改输出耦合器的系数。 基于S矩阵(1)，Pb1,Sat和Pb2,Sat之间的关系可以由[^1]给出



![image2](https://github.com/WaveDragon/test/assets/78013131/b42e5060-70ca-4710-932f-b9b2e5e6fa72)

$$
\begin{equation*} n = {}\frac {V_{b1}^{2}}{V_{b2}^{2}} = {}\frac {P_{b1,{Sat}}}{P_{b2,{Sat}}}{}\frac {Z_{b1,{Sat}}}{Z_{b2,{Sat}}} = {}\frac {(1 - C_{0}^{2})}{C_{0}^{2}}\tag{25}\end{equation*}
$$

其中 n 是  $ V^2_{b1} $  和  $ V^2_{b2} $  的比率。 从(25)可以看出，当PA1和PA2产生的功率(Vb1=Vb2)输送到隔离端口为零时，输出耦合器的系数C0设置为0.707(3dB)。 然而，设计非对称LMBA时，采用非对称输出耦合器是非常有必要的。

### B. 理论验证

为了说明所提出的具有改进输出耦合器的 LMBA，以设置 Icmax=0.6、β1 = 0.5、β2 = 0.75 和 OBO = 10-dB 为例。 在此简述中，假设PA1的输出功率低于PA2的输出功率(0≤n≤1)，则0.707到1ofC0的范围可以通过(25)计算出来。 例如，当确定n=0.73时，可以获得C0=0.76。 代入C0后，用(21)~(24)式即可确定γ1和γ2的值。 为了获得10 dB的OBO电平，可以保证γ1 = 1.6和γ2 = 2.3，如图2（b）所示。 图 3 显示了所提出的 LMBA 的运行行为。 从头


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