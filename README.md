## Задание
<img src = "lab_1_2.png">

<img src = "lab_3_4_5.png">



## Используемая часть карты
### Приблизительные координаты
### lat = 54.7037 lon = 83.01029
<img src = "Simulation/res/region.png">

### Преобразование координат в lat, lon (при условии что карта расположена на сфере)
<div align="center">
lat = asin(z / R)<br>
lon = atan2(y, x)
</div>

### Обратные преобразования

<div align="center">
x = R * cos(lat) * cos(lon)<br>
y = R * cos(lat) * sin(lon)<br>
z = R * sin(lat)
</div>






