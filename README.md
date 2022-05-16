<h1 align="center">Tablut Tactics</h1>

<div align="center">
  Tablut Tactics è un'applicazione grafica creata con l'obiettivo di facilitare la comprensione delle meccaniche di gioco, e l'ideazione di strategie, di Tablut con le regole di Ashton.
  In particolare, permette di inizializzare la tavolo da gioco, con la formazione di partenza, e modificarla a piacimento, muovendo le pedine e creando configurazioni personalizzate.
  Inoltre, è possibile visualizzare i movimenti permessi a ciascuna pedina.
</div>
  
### Demo

### Utilizzo
1. Scaricare l'[ultima versione](https://github.com/mikyll/TablutTactics/releases/latest)
2. Estrarre l'archivio
3. Eseguire il *Launcher*

#### Comandi
- mouse `click sinistro`
  - su una pedina: seleziona/deseleziona la pedina;
  - su uno spazio vuoto (se è stata selezionata una pedina), muove la pedina in quella posizione (non tenendo conto dei vincoli o delle mosse possibili);
- mouse `click destro`: modifica il contenuto di una casella, in base al tipo di pedina selezionata (EMPTY, BLACK, WHITE, KING);
- tastiera `r`: resetta la tavola di gioco con la configurazione iniziale;
- tastiera numeri `0-9`: salva la configurazione corrente nell'indice relativo al numero
- tastiera frecce `<-` e `->`: carica la configurazione salvata all'indice relativo al numero

### Regole di Gioco di Tablut
<img align="right" width="280" height="280" src="https://github.com/mikyll/TablutTactics/blob/main/Tablut/gfx/boardBase.png">

**_Tablut_** è un antico gioco da tavolo di origini nordiche, la cui storia non è del tutto certa.
Esistono diverse regole, ma quelle descritte in questa pagina, chiamate anche "Regole di Ashton", sono le regole adottate per la challenge.

Il tavolo *(eheh tavoletta)* da gioco è costituito da una griglia 9x9. Si gioca in 2 ed i giocatori si alternano muovendo una pedina in ciascun turno. In particolare:
- il **difensore** (bianco), possiede 8 pedine bianche <img width="25" src="https://github.com/Gionnino9000/Gionnino9000/blob/main/Tablut/src/it/unibo/ai/didattica/competition/tablut/gui/resources/White.png"/>
ed 1 re <img width="25" src="https://github.com/Gionnino9000/Gionnino9000/blob/main/Tablut/src/it/unibo/ai/didattica/competition/tablut/gui/resources/ImmagineRe.png"/>.
Deve proteggere il re, aiutandolo a fuggire;
- l'**attaccante** (nero), possiede 16 pedine nere <img width="25" src="https://github.com/Gionnino9000/Gionnino9000/blob/main/Tablut/src/it/unibo/ai/didattica/competition/tablut/gui/resources/Black2.png"/>.
Deve assediare il castello, catturando il re e impedendogli di scappare.

La griglia di gioco comprende delle **caselle speciali**:
- i **campi** <img width="25" src="https://github.com/Gionnino9000/Gionnino9000/blob/main/Tablut/src/it/unibo/ai/didattica/competition/tablut/gui/resources/camp.png"/>, 
sono le posizioni di partenza delle pedine nere, su cui si possono muovere esclusivamente loro. Se una pedina esce da un campo, poi non può più rientrare;
- il **castello** <img width="25" src="https://github.com/Gionnino9000/Gionnino9000/blob/main/Tablut/src/it/unibo/ai/didattica/competition/tablut/gui/resources/castle.png"/>,
è la posizione di partenza del re. Come per i campi, solo il re può trovarsi in questa casella, ma se esce non può più rientrare;
- le **vie di fuga** <img width="25" src="https://github.com/Gionnino9000/Gionnino9000/blob/main/Tablut/src/it/unibo/ai/didattica/competition/tablut/gui/resources/escape.png"/>.
Se il re si muove su una di queste caselle, il bianco vince.

<img align="right" width="280" height="280" src="https://github.com/mikyll/TablutTactics/blob/main/Tablut/gfx/board_initial_state.png">

**Movimenti** possibili:
- le pedine si muovono ortogonalmente (ovvero non possono fare mosse in diagonale), di un numero qualsiasi di caselle, ma non possono scavalcare i campi ed il castello, o altre pedine;
- le pedine nere si possono muovere liberamente all'interno dello stesso campo, finché non escono, dopodiché non potranno più rientrare.

Le pedine possono essere **catturate**:
- una pedina bianca o nera viene catturata se l'avversario la circonda con due pedine su lati opposti;
- il re può essere catturato solo se viene circondato su ogni lato;
- è possibile catturare più di una pedina alla volta e la cattura dev'essere "attiva": se una pedina si sposta fra due pedine avversarie non viene catturata.

Esistono anche **casi speciali** di catture:
- una pedina bianca o nera può venire catturata anche se si trova in una casella adiacente ad un campo o al castello, e una pedina avversaria si sposta sulla casella opposta 
(i campi ed il castello si comportano come una sorta di "barriera", non importa se tale casella è occupata oppure no);
- se il re si trova in una casella adiacente ad uno o più campi o al castello, è sufficiente circondarlo in tutti i restanti lati liberi per catturarlo.

**Inizio** del gioco: il bianco muove per primo.

Il gioco **termina** quando:
- il re raggiunge una via di fuga, in questo caso <ins>vince il bianco</ins>;
- il re viene catturato, in questo caso <ins>vince il nero</ins>;
- un giocatore non può più muovere pedine, in questo caso tale giocatore perde;
- lo stato di gioco si ripete due volte, in questo caso si ha un pareggio.

### Sviluppi Futuri
- [ ] Caricamento/Salvataggio dello stato verso/da file
- [ ] Attivazione delle meccaniche del gioco (pedine mangiate, movimento vincolato, gestione turni), tramite 'g'
