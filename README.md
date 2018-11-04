# Software Development 
### Ανάπτυξη Λογισμικού για Πληροφοριακά Συστήματα

Στην συγκεκριμένη εργασία, υλοποιείται η συνάρτηση **JOIN** ανάμεσα σε δύο σχέσεις, ανάλογα με το πεδίο που επιλέγεται για σύγκριση. 
Ο τρόπος επίλυσης έγινε με την υλοποίηση του **Radix Hash Join** αλγορίθμου. Για την συνάρτηση κατακερματισμού η οποία χωρίζει τις τιμές σε buckets, χρησιμοποιήσαμε την εύρεση του αριθμού των τελευταίων **4 bits** του αριθμού. Για την δεύτερη συνάρτηση κατακερματισμού, η οποία επιλέγει τα στοιχεία για το ευρετήριο, χρησιμοποιήσαμε την εύρεση του αριθμού των τελευταίων **8 bits**. 

### Prerequisites - Προϋποθέσεις
Για την εγκατάσταση της εφαρμογής, το περιβάλλον πρέπει να είναι **Linux** ενώ η έκδοση του **gcc** πρέπει να είναι **5.4+**.
Για τον έλεγχο του version
`gcc -v`. 
Για την ενημέρωση του 
```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install gcc-6
```

### Installing - Εγκατάσταση
Για την εγκατάσταση της εφαρμογής:
1. Ανοίξτε τον φάκελο **Software_Development**.
2. Άνοιγμα **cmd** στον συγκεκριμένο φάκελο.
3. Εκτέλεση εντολής `make`.

## Running - Εκτέλεση
Για την εκτέλεση, απλώς εκτελέστε την εντολή `./joinProgram`.

## Authors - Συγγραφείς
- [Στεφανία Πάτσου](https://github.com/PiStefania)
- [Ανδρέας Τσόλκας](https://github.com/andreasgtech)
- [Ορέστης Γαρμπής](https://github.com/Pantokratoras7)

## Reference - Αναφορά
- Cagri Balkesen, Jens Teubner, Gustavo Alonso, and M. Tamer Özsu. [Main-Memory
Hash Joins on Multi-Core CPUs: Tuning to the Underlying Hardware](https://ieeexplore.ieee.org/document/6544839). Proc. of the 29th
International Conference on Data Engineering (ICDE 2013) , Brisbane, Australia, April 2013.
