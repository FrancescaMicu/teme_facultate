#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

// TextEditor structure - TODO: define your own fields here
typedef struct TPiece {
  int buffType; // 0 - buffer original, 1 - buffer adaugat
  int startIdx;
  int length;
} Piece;

typedef struct TTextEditor {
  // TODO: define any fields you need for your implementation
  char *firstBuff;
  char *newBuff;
  int capNewBuff;
  int idxWrite;
  Piece *allPieces;
  int nrPieces;
  int capNrPieces;
  int cursor;
  int totalLen;
} TextEditor;

// ============================================================================
// API Functions - You MUST implement all of these
// ============================================================================

// Create a new text editor
// filename: if not NULL, load content from this file
// text: if not NULL (and filename is NULL), initialize with this text
// global_cursor: initial cursor position
TextEditor *create_table(const char *filename, const char *text, int global_cursor);

// Move cursor by 'advance' positions (can be negative for backwards)
void advance_cursor(TextEditor *editor, int advance);

// Get current cursor position
int show_global_cursor(TextEditor *editor);

// Get total text length
int show_total_len(TextEditor *editor);

// Insert text at current cursor position
void add_text(TextEditor *editor, char *text);

// Delete 'length' characters before cursor
void delete_text(TextEditor *editor, int length);

// Extract full text as allocated string (caller must free)
char *extract_current_text(TextEditor *editor);

// Save text to file or return via text pointer
void save_current_text(TextEditor *editor, const char *filename, char **text, int *global_cursor);

// ============================================================================
// Helper functions (optional - you can define your own)
// ============================================================================

#endif // TEXT_EDITOR_H
