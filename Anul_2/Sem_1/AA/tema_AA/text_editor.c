#include "text_editor.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

TextEditor* create_table(const char* filename, const char* text,
                         int global_cursor) {
  // TODO: Implement this function
  TextEditor* textEdit = (TextEditor*)malloc(sizeof(TextEditor));
  if (textEdit == NULL) {
    return NULL;
  }

  int initSize;
  //  initializare structura si alocare buffere
  if (filename == NULL && text == NULL) {
    textEdit->firstBuff = (char*)malloc(sizeof(char));
    if (textEdit->firstBuff == NULL) {
      free(textEdit);
      return NULL;
    }
    initSize = 0;
    textEdit->firstBuff[0] = '\0';
  } else if (filename == NULL) {
    textEdit->firstBuff = strdup(text);
    initSize = strlen(text);
  } else {  //  text == NULL
    FILE* file = fopen(filename, "r");
    if (!file) {
      free(textEdit);
      return NULL;
    }

    //  determinare dimensiune fisier
    fseek(file, 0, SEEK_END);
    long fileCap = ftell(file) + 1;
    rewind(file);

    textEdit->firstBuff = (char*)malloc(sizeof(char) * fileCap);
    if (textEdit->firstBuff == NULL) {
      free(textEdit);
      return NULL;
    }

    char* line = NULL;
    int lineSize = 0;
    int currIdx = 0;
    int nrChars = getline(&line, &lineSize, file);
    while (nrChars != -1) {
      memcpy(textEdit->firstBuff + currIdx, line, nrChars);
      currIdx += nrChars;
      nrChars = getline(&line, &lineSize, file);
    }
    textEdit->firstBuff[currIdx] = '\0';
    initSize = currIdx;

    free(line);
    fclose(file);
  }

  //  daca la inceput nu exista text, aloc spatiu pentru 100 de caractere
  if (initSize == 0) {
    textEdit->capNewBuff = 100;
  } else {
    textEdit->capNewBuff = initSize;
  }

  textEdit->newBuff = malloc(sizeof(char) * textEdit->capNewBuff);
  if (textEdit->newBuff == NULL) {
    free((void*)textEdit->firstBuff);
    free(textEdit);
    return NULL;
  }
  textEdit->idxWrite = 0;

  textEdit->nrPieces = 1;

  textEdit->allPieces = (Piece*)malloc(sizeof(Piece) * textEdit->nrPieces);
  if (textEdit->allPieces == NULL) {
    free((void*)textEdit->firstBuff);
    free(textEdit->newBuff);
    free(textEdit);
    return NULL;
  }

  //  initializare prima piesa in bufferul original
  textEdit->allPieces[0].buffType = 0;
  textEdit->allPieces[0].startIdx = 0;
  textEdit->allPieces[0].length = initSize;

  textEdit->capNrPieces = 1;

  textEdit->cursor = global_cursor;

  textEdit->totalLen = initSize;

  return textEdit;
}

void advance_cursor(TextEditor* editor, int advance) {
  // TODO: Implement this function
  int testCurs = editor->cursor + advance;

  //  verificare sa fie cursorul in limitele valide
  if (testCurs < 0) {
    editor->cursor = 0;
    return;
  }
  int totLen = show_total_len(editor);
  //  lungimea totala a bufferelor
  if (testCurs > totLen) {
    editor->cursor = totLen;
    return;
  }

  editor->cursor += advance;
}

int show_global_cursor(TextEditor* editor) {
  // TODO: Implement this function
  if (editor == NULL) {
    return 0;
  }
  return editor->cursor;
}

int show_total_len(TextEditor* editor) {
  // TODO: Implement this function
  if (editor == NULL) {
    return 0;
  }
  return editor->totalLen;
}

void add_text(TextEditor* editor, char* text) {
  // TODO: Implement this function
  // asigurare capacitate in newBuff
  int newLenAdd = strlen(text);
  int capIncreased = 0;
  //  verificarea capacitatii
  while (editor->idxWrite + newLenAdd >= editor->capNewBuff) {
    //  dublarea capacitatii
    editor->capNewBuff = 2 * editor->capNewBuff;
    capIncreased = 1;
  }
  if (capIncreased == 1) {
    char* newBuffRealloc = realloc(editor->newBuff, editor->capNewBuff);
    if (newBuffRealloc == NULL) {
      return;
    }
    editor->newBuff = newBuffRealloc;
  }
  memcpy(editor->newBuff + editor->idxWrite, text, newLenAdd);

  //  creare piesa
  Piece newPiece;
  newPiece.buffType = 1;
  newPiece.length = newLenAdd;
  newPiece.startIdx = editor->idxWrite;
  //  actualizare indice in editor
  editor->idxWrite += newLenAdd;
  //  parcurgere piese
  int currLen = 0;
  int foundPieceIdx = -1;
  int idxToSplit;
  for (int i = 0; i < editor->nrPieces; i++) {
    if (editor->cursor <= currLen + editor->allPieces[i].length &&
        editor->cursor >= currLen) {
      foundPieceIdx = i;
      idxToSplit = editor->cursor - currLen;
      break;
    }
    currLen += editor->allPieces[i].length;
  }
  if (foundPieceIdx == -1) {
    return;
  }
  capIncreased = 0;
  while (editor->nrPieces + 2 >= editor->capNrPieces) {
    //  dublarea capacitatii
    editor->capNrPieces = 2 * (editor->capNrPieces + 2);
    capIncreased = 1;
  }
  if (capIncreased == 1) {
    Piece* newPiecesRealloc =
        realloc(editor->allPieces, sizeof(Piece) * editor->capNrPieces);
    if (newPiecesRealloc == NULL) {
      return;
    }
    editor->allPieces = newPiecesRealloc;
  }

  //  cursorul e la inceput, se insereaza la inceput
  if (idxToSplit == 0) {
    //  shiftare la dreapta
    memmove(&editor->allPieces[foundPieceIdx + 1],
            &editor->allPieces[foundPieceIdx],
            (editor->nrPieces - foundPieceIdx) * sizeof(Piece));
    editor->nrPieces++;
    editor->allPieces[foundPieceIdx] = newPiece;
    //  cursorul e la final, se insereaza la final
  } else if (idxToSplit == editor->allPieces[foundPieceIdx].length) {
    //  shiftare la dreapta cu 2 pozitii
    memmove(&editor->allPieces[foundPieceIdx + 2],
            &editor->allPieces[foundPieceIdx + 1],
            (editor->nrPieces - (foundPieceIdx + 1)) * sizeof(Piece));
    editor->nrPieces += 1;
    editor->allPieces[foundPieceIdx + 1] = newPiece;
    //  cursorul e in interior, se sparge piesa in 3
  } else {
    //  creare piesa prin shiftare de dupa index
    Piece splitRightSide;
    splitRightSide.buffType = editor->allPieces[foundPieceIdx].buffType;
    splitRightSide.startIdx =
        editor->allPieces[foundPieceIdx].startIdx + idxToSplit;
    splitRightSide.length =
        editor->allPieces[foundPieceIdx].length - idxToSplit;
    //  shiftare la dreapta cu 2 pozitii
    memmove(&editor->allPieces[foundPieceIdx + 3],
            &editor->allPieces[foundPieceIdx + 1],
            (editor->nrPieces - (foundPieceIdx + 1)) * sizeof(Piece));
    editor->nrPieces += 2;
    editor->allPieces[foundPieceIdx + 1] = newPiece;
    editor->allPieces[foundPieceIdx + 2] = splitRightSide;
    editor->allPieces[foundPieceIdx].length = idxToSplit;
  }
  editor->cursor += newPiece.length;
  editor->totalLen += newLenAdd;
}

void delete_text(TextEditor* editor, int length) {
  // TODO: Implement this function
  if (length > editor->cursor) {
    length = editor->cursor;
  }
  int startDelIdx = editor->cursor - length;
  int currLen = 0;
  //  capNrPieces este folosit drept capacitate pentru array-ul newAllPieces
  Piece* newAllPieces = (Piece*)malloc(sizeof(Piece) * editor->capNrPieces);
  if (newAllPieces == NULL) {
    return;
  }
  int newNrPieces = 0;
  for (int i = 0; i < editor->nrPieces; i++) {
    //  piesa e in afara zonei de stergere
    int origLen = editor->allPieces[i].length;
    if (currLen + editor->allPieces[i].length <= startDelIdx ||
        editor->cursor <= currLen) {
      newAllPieces[newNrPieces++] = editor->allPieces[i];
    } else {
      //  verificarea capacitatii pentru posibilitatea inserarii a doua piese
      int capIncreased = 0;
      while (newNrPieces + 2 >= editor->capNrPieces) {
        //  dublarea capacitatii
        editor->capNrPieces *= 2;
        capIncreased = 1;
      }
      if (capIncreased == 1) {
        Piece* newPiecesRealloc =
            realloc(newAllPieces, sizeof(Piece) * editor->capNrPieces);
        if (newPiecesRealloc == NULL) {
          free(newAllPieces);
          return;
        }
        newAllPieces = newPiecesRealloc;
      }
      //  piesa incepe inainte de zona de stergere
      if (currLen < startDelIdx) {
        Piece leftSplit = editor->allPieces[i];
        leftSplit.length = startDelIdx - currLen;
        newAllPieces[newNrPieces++] = leftSplit;
      }
      //  pastrarea partii din dreapta a piesei daca aceasta trece de cursor
      if (currLen + origLen > editor->cursor) {
        Piece rightPiece = editor->allPieces[i];
        rightPiece.startIdx += editor->cursor - currLen;
        rightPiece.length = currLen + origLen - editor->cursor;
        newAllPieces[newNrPieces++] = rightPiece;
      }
    }
    currLen += origLen;
  }
  free(editor->allPieces);
  editor->allPieces = newAllPieces;
  editor->nrPieces = newNrPieces;
  // stergere in stanga cursorului
  editor->cursor -= length;
  editor->totalLen -= length;
}

char* extract_current_text(TextEditor* editor) {
  // TODO: Implement this function
  int totLen = show_total_len(editor) + 1;
  //  alocarea bufferului
  char* totalBuff = (char*)malloc(sizeof(char) * totLen);
  if (totalBuff == NULL) {
    return NULL;
  }

  //  copierea datelor in buffer
  int currIdx = 0;
  for (int i = 0; i < editor->nrPieces; i++) {
    if (editor->allPieces[i].buffType == 0) {
      memcpy(totalBuff + currIdx,
             editor->firstBuff + editor->allPieces[i].startIdx,
             editor->allPieces[i].length);
    } else {
      memcpy(totalBuff + currIdx,
             editor->newBuff + editor->allPieces[i].startIdx,
             editor->allPieces[i].length);
    }
    currIdx += editor->allPieces[i].length;
  }
  totalBuff[totLen - 1] = '\0';
  return totalBuff;
}

void save_current_text(TextEditor* editor, const char* filename, char** text,
                       int* global_cursor) {
  // TODO: Implement this function
  //  salvarea cursorului
  if (global_cursor != NULL) {
    (*global_cursor) = editor->cursor;
  }

  char* textBuff = extract_current_text(editor);
  if (textBuff == NULL) {
    return;
  }
  //  scriere in fisier
  if (filename != NULL) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
      free(textBuff);
      return;
    }
    fprintf(file, "%s", textBuff);
    fclose(file);
  }

  //  scriere in campul text
  if (text != NULL) {
    (*text) = strdup(textBuff);
  }

  free(textBuff);
}
