
# Kinematyka

## Ruchy
* jednostajny prostoliniowy $a_x = 0$
* jednostajnie przyspieszony $a_x = const$
* rzut ukośny
* ruch po okręgu
	* promień krzywizny: $R = \frac{v^2}{a_n}$ gdzie $a_n$ to przyspieszenie normalne, i.e. przyspieszenie zwrócone do środka okręgu

# Dynamika

## Układ inercjalny vs nieinercjalny

### Inercjalny
* przyspieszenie pojawia się wtw. jako rezultat niezrównoważonej siły zewnętrznej, i.e. zachowana jest *pierwsza zasada Newtona
* typ w windzie $\implies$ szyb windy

### Nieinercjalny
* nie jest zachowana 1 zasada Newtona, ciało może mieć wirtualne przyspieszenia
* typ w windzie $\implies$ typ

[GPT regurgitation](https://chat.openai.com/share/51668034-bbe1-45bb-9a3a-d765b748c6f3)

## Pęd

* zdefiniowany jako $$\vec{p} = m \cdot \vec{v}$$
* siła działająca na ciało $\vec{F}$ jest pochodną pędu $$\frac{d\vec{p}}{dt} = \frac{d(m \cdot \vec{v})}{dt} = m \cdot \frac{d\vec{v}}{dt} = m \cdot \vec{a} = \vec{F}$$
* [**zasada zachowania pędu**](https://en.wikipedia.org/wiki/Momentum#Conservation)

## Energia

### Energia potencjalna

Siła działająca na obiekt jest negatywnym gradientem energii potencjalnej $$- \nabla U = F$$ w przypadku energii potencjalnej ciała na wysokości $h$ przy spadku swobodnym $$-\frac{\delta U}{\delta h} = -\frac{\delta (mgh)}{\delta h} = -mg$$ 
### Energia kinetyczna

$$E_k = \frac{mv^2}{2}$$ 
## Praca

Praca jest zdefiniowana jako różnica energii kinetycznej lub ujemna różnica energii potencjalnej, i.e. $$W = \Delta E_k \space \lor W = -\Delta U$$
jeśli siła działająca na ciało nie zależy od drogi, to $$W = \int^{r_1}_{r_2}\vec{F}dr$$
#### Siła zachowawcza 
Siła działająca na ciało niezależnie od obranej ścieżki wykona tę samą pracę

#### Moc
pochodna pracy, i.e. $p = \frac{dW}{dt}$ 


## Oscylator harmoniczny

Siła działająca na ciało w oscylatorze harmonicznym jest proporcjonalna do wychylenia $F \sim -\Delta x$. Przy założeniu, że relacja współczynnika elastyczności jest liniowa do wychylenia jest liniowa: 
$$F = -kx \implies ma = -kx \implies m\ddot{x} = -kx \implies  \ddot{x} + \frac{k}{m}x = 0$$
Przykładem takiego ruchu jest ciało na sprężynie z pominięciem oporów. Po rozwiązaniu równania różniczkowego otrzymujemy równanie na położenie ciała $$x = A_1 e^{\lambda _1t} + A_2 e^{\lambda _2t}$$ biorąc wielomian charakterystyczny bazowego równania $$\lambda ^2 + \frac{k}{m} = 0$$otrzymujemy $$\lambda = \sqrt{-\frac{k}{m}} \implies \lambda = \pm i \sqrt{\frac{k}{m}}$$
oznaczmy $$\omega _0 \coloneqq \sqrt{\frac{k}{m}}$$ ostatecznie możemy następująco wyrazić równanie prędkości ciała $$v = \frac{dx}{dt} = A_1i\omega _0 e^{\omega _0 t} - A_2i\omega _0 e^{-\omega _0 t}$$
zauważmy, że $A_1 = A_2$, stąd możemy wyrazić równanie na ruch $$x = \frac{A}{2} (e^{\omega _0 t} + e^{-\omega _0 t}) = Acos(\omega _0 t)$$ skoro $x(t)$ jest funkcją okresową, to $x(t) = x(t + T)$, gdzie $T$ jest okresem funkcji zatem $$Acos(\omega _0t + y_0) = Acos(\omega _0(t + T) + y_0) \implies \omega _0t + y_0 = \omega _0t + \omega _0T + y_0 - 2\pi \implies T = \frac{2\pi}{\omega _0} = \frac{1}{f}$$
### Tłumienie oscylatora
W przypadku tłumienia w najprostszym układzie zakładamy, że siła oporu $F_r$ jest proporcjonalna do prędkości ciała, i.e. $F_r \sim v \implies F_r = \gamma v$. Po dodaniu tej siły do równania ruchu otrzymujemy $$ma = -kx - \gamma \frac{dx}{dt} \implies \ddot{x} + \frac{m}{\gamma}\dot{x} + \omega _0 ^ 2x = 0$$
 po rozwiązaniu otrzymamy następujące równanie położenia $$x = A_1e^{-\beta t}cos(\omega _0t)$$ $$\beta \coloneqq \frac{m}{2\gamma}$$$\beta$ oznacza współczynnik tłumienia, który ostatecznie włączamy do częstości własnej drgań tłumionych $$\omega = \sqrt{{\omega _0 ^2 - \beta ^2}}$$ przy tłumieniu rozpatrujemy dwa przypadki
 1. $\beta \gt \omega _0$ - nie zachodzi oscylacja
 2. $\beta \lt \omega$ - zachodzi oscylacja

[Artykuł AGH - oscylator tłumiony](https://home.agh.edu.pl/~kakol/efizyka/w12/main12d.html)

### Oscylator tłumiony wymuszony
Tutaj do naszego tłumionego oscylatora harmonicznego dodajemy siłę wymuszającą przyłożoną do drgającego ciała wyrażonego funkcją $$F(t) = F_0 sin(\omega t)$$ analogicznie do do tłumienia, dodajemy siłę wymuszającą do równania ruchu $$ma = -kx - \gamma \frac{dx}{dt} + F(T)$$ wprowadzając oznaczenia $$\tau \coloneqq \frac{m}{\gamma}, \omega _o ^2 \coloneqq \frac{k}{m}, \alpha _0 \coloneqq \frac{F_0}{m}$$ otrzymujemy równianie ruchu oscylatora tłumionego z wymuszeniem $$\ddot{x} + \frac{1}{\tau}\frac{dx}{dt} + \omega _0^2x = \alpha _0 sin(\omega t)$$ w tym przypadku $\omega$ jest częstością siły wymuszającej a $\omega _0$ bezzmiennie częstością własną układu.

***Drgania układu zachodzą z częstością siły wymuszającej***

W ogólności nasz ruch jest złożeniem funkcji siły wymuszającej i położenia ciała $$A_1 cos(\omega t) + A_2 sin(\omega t) = Asin(\omega t + \phi)$$ stąd mamy przesunięcie fazowe $\phi$, które określa o ile maksimum siły wyprzedza położenie ciała.

### Rezonans
W zależności od zbliżenia się maksimów położenia i siły będą się zbliżały, i.e. przesunięcie fazowe $\phi$ będzie się zmniejszać, amplituda drgań będzie wzrastać, co nazywamy rezonansem

[Artykuł agh - drgania wymuszone](https://home.agh.edu.pl/~kakol/efizyka/w12/main12e.html)

# Fale mechaniczne
Fale rozpatrujemy matematycznie jako propagację wychylenie fragmentu ośrodka sprężystego z położenia równowagi. Prędkość takiego fragmentu wzdłuż kierunku propagacji jako $$v_x = \sqrt{\frac{N}{\mu}}$$ gdzie $N$ to naprężenie ośrodka a $\mu$ to gęstość wyrażona jako $\frac{\Delta m}{\Delta \mu}$ .

### Energia fali mechanicznej
Energia fali mechanicznej jest zależna od prędkości fragmentu w kierunku oscylacji. Zacznijmy od zmiany energii kinetycznej kawałka ośrodka $$\Delta E_k = \frac{\Delta m \cdot v_y^2}{2}$$ niech równanie na prędkość w kierunku oscylacyjnym będzie wyrażone $$v_y = -A \omega cos(hx - \omega t)$$ i wiedząc, że $\Delta m = \mu \cdot \Delta x$, gdzie $x$ jest położeniem w kierunku propagacji ostatecznie otrzymujemy $$\Delta E_k = \frac{1}{2} \mu v_x A^2 \omega ^2 \cos ^2(hx - \omega t)$$
mając zmianę energii, możemy wyznaczyć moc chwilową fali $$p = \frac{\Delta E_k}{\Delta t} = \Delta E_k$$
aby obliczyć średnią energię na większym odcinku czasu, bierzemy średnią z naszej mocy, i.e. całka oznaczona na okresie podzielona przez ten okres

[Artykuł AGH](https://home.agh.edu.pl/~kakol/efizyka/w13/main13d.html)

### Interakcje między falami
* ***Superpozycja** jest sumą algebraiczną fal. 
* **Interferencja** jest nachodzeniem się fal

#### Fale stojące 
Przypadek kiedy mamy dwie fale o identycznych częstotliwościach i amplitudach, ale przeciwnych kierunkach propagacji, np. fala, która odbija się od granicy ośrodka i nakłada się sama na siebie. $$y_1 = A\sin(kx + \omega t),~~ y_2 = A\sin(kx - \omega t)$$ wtedy $$y = y_1 + y_2 = 2Asin(kx)cos(\omega t)$$ zauważmy, że mamy do czynienia z równaniem ruchu harmonicznego w postaci $$y = A'\sin(kx)$$ gdzie amplituda jest wyrażona $A' = 2A\sin(kx)$. Stąd widać, że w naszej fali stojącej będą występować punkty, gdzie amplituda zawsze będzie wynosić zero (*węzły*) niezależnie od czasu, czyli dla punków $kx \in \{n \in \mathbb{Z} | n\pi\}$. Analogicznie punkty o największej amplitudzie (*strzałki*) tworzą dla punktów  $kx \in \{n \in \mathbb{Z} | \frac{\pi}{2} + n\pi\}$.

[Artykuł AGH](https://home.agh.edu.pl/~kakol/efizyka/w13/main13e.html)

# Elektrostatyka

## Siła oddziaływania między dwoma cząstkami
Każde dwa ładunki punktowe $q_1$, $q_2$ oddziałują na siebie z następującą zależnością $$F = k\frac{q_1q_2}{r^2}$$ gdzie $$k \coloneqq \frac{1}{4\pi \epsilon _0}$$ [Artykuł AGH](https://home.agh.edu.pl/~kakol/efizyka/w17/main17b.html)

### Pole elektryczne
Pole elektryczne jest analogiczne do pola grawitacyjnego. Żeby wyznaczyć natężenie pola elektrycznego potrzebujemy umieścić *ładunek próbny* w tym że polu i wyliczyć siłę na niego oddziałującą. $$E = \frac{F}{q}$$ siłę opisujemy $$F = k\frac{Qq}{r^2}$$ zatem łącząc w jedno $$E = \frac{1}{q}k\frac{Qq}{r^2}\hat{r} = k\frac{Q}{r^2}\hat{r}$$ gdzie $r$ jest odległością między cząstkami a $\hat{r}$ jest wektorem jednostkowym zgodnym z kierunkiem siły między tymi cząstkami. Dla $n$ ładunków, pole elektryczne jest sumą wektorową natężeń pola dla każdego punktu.

[Artykuł AGH](https://home.agh.edu.pl/~kakol/efizyka/w17/main17c.html)

### Potencjał elektryczny
Analogicznie do mechanicznej energii potencjalnej, potencjał pola elektrycznego jest negatywnym gradientem natężeniem pola elektrycznego $$-\nabla V = \vec{E}$$ponieważ pole elektryczne jest polem zachwawczą, praca wykonana przez cząstkę w polu elektrycznym jest zmianą jej energii potencjalnej. $$W = q(V_2 - V_1)$$
[Opracowanie zpe](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwj8-LT1zO3_AhW2BxAIHTD5CvYQFnoECAgQAw&url=https%3A%2F%2Fzpe.gov.pl%2Fpdf%2FP1696T7BC%23%3A~%3Atext%3DZatem%2520przesuni%25C4%2599cie%2520%25C5%2582adunku%2520wymaga%2520wykonania%2Cta%2520r%25C3%25B3wna%2520jest%2520wykonanej%2520pracy.&usg=AOvVaw2HyJaTeEEvYiN0thpcCf1d&opi=89978449)

### Dipol elektryczny
Układ dwóch różnoimiennych ładunków elektrycznych o tych samych wartościach bezwzględnych, i.e. plus i minus obok siebie. [Moment dipolowy](https://pl.wikipedia.org/wiki/Elektryczny_moment_dipolowy) wyrażony jako iloczyn ładunku dodatniego dipolu i odległości między ładunkami $p = qd$ ma wpływ na moment siły oddziałujący na dipol w polu elektryczny w polu $E$ $$M = p \times E$$




