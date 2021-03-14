Probleme cu implementarea:

  -Stack overflow la valori de peste 10^5 pe care nu stiu cum sa o rezolv. \n
  -Nu am implementat mai multe teste decat random array. \n

Observatii:

  -Bubble Sort este cel mai incet indiferent de date, dar este cel mai simplu de codat. Este de asemenea extrem de incet daca array-ul este deja sortat, dar descrescator. \n
  -Merge Sort este putin mai incet decat Quick Sort in majoritatea cazurilor, dar nu are probleme la numere mici si necesita mai multa memorie. \n 
  -Quick Sort este extrem de incet la numere mici, dar tinde sa fie mai rapid decat Merge Sort la numere mari. Cel mai probabil am ales pivotul in mod prost. \n
  -Count Sort in testele mele tinde sa fie cel mai rapid insa nu sunt sigur ca l-am implementat corect. Functia care verifica daca sirul este sortat spune ca merge, 
  deci nu stiu. \n
  -Radix Sort avand la baza un count sort cu baza 10 tinde sa fie mai incet decat count sort cu cat creste marimea datelor. \n
  -std::sort este mai rapod pe testele mele decat Quick Sort, dar nu la fel de rapid ca si Radix Sort indiferent de test. \n
  
  Teste:
  
  ![alt text](https://i.imgur.com/yoLfFWV.png)
  ![alt text](https://i.imgur.com/B2j0WIf.png)
  ![alt text](https://i.imgur.com/PZq86eJ.png)
