/*Я сделал ускорение симметризованных методов, но в одном месте вылетает core dump - я не знаю, как с этим бороться:( 
update: я это поборол - оказалось, что всё это время Гаусс-Зейдель был написан с ошибкой(один из его вариаций)*/

/*Я написал BiCG, но он просто не работает. Я транспонировал csr матрицу и правил это, я закидывал положительно определенную и симметричную, но не сходилось.
Мб этот метод настолько не стабильный "\('__')/" */

Сравнение csr и dense матриц.
![Иллюстрация к проекту](https://github.com/PaulBurs/SLAE/blob/main/test/dense_vs_csr_matrix.png)

Сравненние итерационных методов: простейший метод, метод Якоби, метод Гаусса Зейделя и ускорение Чебышева. + QR-рещение.
![Иллюстрация к проекту](https://github.com/PaulBurs/SLAE/blob/main/test/iter_solution_versus_csr_matrix.png)

Сравнение простейших итерационных методов с SGD, sGS и SOR. Также добавил CGS(BiCG не сходится (-__-)).
![Иллюстрация к проекту](https://github.com/PaulBurs/SLAE/blob/main/test/iter_solution_versus_csr_matrix1.png)

Зависимость времени сходимости SOR от параметра omega.
![Иллюстрация к проекту](https://github.com/PaulBurs/SLAE/blob/main/test/time_SOR_omega.png)

Лучше всего себя показал SGD - он дал наилучшую точность почти при наименьшем времени. Это может быть связано с низкой потерей тончости при арифметических вычислениях.
SOR получился слишком плохим. Он сходится за 10-ки мс - слишком долго расчитывать omega, но для честности omega нужно счиать каждый раз. Рассчет omega гораздо дороже, чем обычный GS. 

Вот тут сравнение симметризованного ускорения для разных методов. SGD просто прекрасен - за бесплатно дропает e-14 точность
![Иллюстрация к проекту](https://github.com/PaulBurs/SLAE/blob/main/test/symmetry_acceleration.png)

Вот тут сравнение на эллиптической матрице 100*100 сравнение решенние разными методами: симметризованными и не только. Главый вывод по этой части - CGS лучше всех, но каждый метод очень быстро справляется с решением эллиптической задачи.
![Иллюстрация к проекту](https://github.com/PaulBurs/SLAE/blob/main/test/symmetry_versus.png)
