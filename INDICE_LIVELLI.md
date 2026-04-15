# 🎮 GraviCLI - Indice Livelli

## Livelli Disponibili

### Tutorial e Prova
- **tutorial.txt** - Livello tutorial introduttivo
- **prova.txt** - Livello di prova
- **griglia.txt** - Livello di test griglia

### Nuovi Livelli Creati

#### 1️⃣ **livello1_corridoio.txt** ⭐ Facile
```
Descrizione: Corridoio semplice in linea retta
Obiettivo: Imparare i movimenti base della gravità
Meccaniche: Movimento lineare
Tempo stimato: 2-3 minuti
Proiettili: 0
Ostacoli: 0
```

#### 2️⃣ **livello2_labirinto.txt** ⭐⭐ Intermedio
```
Descrizione: Navigazione attraverso sezioni divise
Obiettivo: Imparare a cambiare direzione frequentemente
Meccaniche: Cambio di gravità, salti tra sezioni
Tempo stimato: 5-7 minuti
Proiettili: 4
Ostacoli: Muri divisori
Bonus: Raccogliere proiettili extra
```

#### 3️⃣ **livello3_salti_gravita.txt** ⭐⭐ Intermedio-Avanzato
```
Descrizione: Piattaforme con cambio di gravità
Obiettivo: Padroneggiare i salti gravitazionali
Meccaniche: Salti precisati, gravità multi-direzionale
Tempo stimato: 7-10 minuti
Proiettili: 6
Ostacoli: Blocchi singoli
Sfida: Precisione nel cambio di gravità
```

#### 4️⃣ **livello4_puzzle.txt** ⭐⭐⭐ Avanzato
```
Descrizione: Puzzle con raccolta bonus
Obiettivo: Pianificare il percorso con raccolta ottimale
Meccaniche: Percorsi multipli, raccolta bonus
Tempo stimato: 10-15 minuti
Proiettili: 8
Ostacoli: Muri da distruggere
Sfida: Trovare il percorso più efficiente
```

#### 5️⃣ **livello5_spirale.txt** ⭐⭐⭐ Difficile
```
Descrizione: Percorso a spirale con ostacoli progressivi
Obiettivo: Test finale di padronanza
Meccaniche: Tutte le meccaniche combinate
Tempo stimato: 15-20 minuti
Proiettili: 10
Ostacoli: Muri complessi
Sfida: Combinazione di tutte le abilità
```

## 📊 Curva di Difficoltà

```
Difficoltà
    ^
    |     livello5_spirale
    |     (Difficile)
    |
    |     livello4_puzzle
    |     livello3_salti
    |     (Intermedio-Avanzato)
    |
    |     livello2_labirinto
    |     (Intermedio)
    |
    |     livello1_corridoio
    |     (Facile)
    |
    +-----> Progressione
```

## 🎯 Consigli di Gioco

### Per i Principianti
1. Inizia con `livello1_corridoio.txt`
2. Usa il tasto D per il DEBUG e visualizzare la griglia
3. Impara a padroneggiare un cambio di gravità alla volta
4. Pratica il backspace per correggere gli errori

### Per i Giocatori Intermedi
1. Passa a `livello2_labirinto.txt` e `livello3_salti_gravita.txt`
2. Racconta i proiettili (.) e pianifica come usarli
3. Inizia a combinare più cambi di gravità
4. Usa SKIP in modo strategico

### Per i Professionisti
1. Affronta `livello4_puzzle.txt` e `livello5_spirale.txt`
2. Ottimizza il percorso per velocità
3. Raccogli TUTTI i proiettili possibili
4. Completa il livello con il minimo di mosse

## 🛠️ Come Caricare un Livello Diverso

Modifica il file `main.cpp` riga 126:
```cpp
campo.carica_campo("livello1_corridoio.txt");  // Cambia il nome del file qui
```

Quindi ricompila:
```bash
./compila.sh    # Su Linux/Mac
./compila.bat   # Su Windows
```

## 📈 Statistiche Livelli

| Livello | Larghezza | Altezza | Ostacoli | Proiettili | Difficoltà |
|---------|-----------|---------|----------|-----------|-----------|
| livello1 | 50 | 5 | 0 | 0 | ⭐ |
| livello2 | 50 | 10 | Media | 4 | ⭐⭐ |
| livello3 | 45 | 15 | Pochi | 6 | ⭐⭐ |
| livello4 | 52 | 15 | Muri | 8 | ⭐⭐⭐ |
| livello5 | 60 | 15 | Molti | 10 | ⭐⭐⭐ |

---
**Ultimo aggiornamento**: 2026-04-14
**Versione**: 1.0

