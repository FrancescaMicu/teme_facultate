package org.example;

import java.time.LocalDateTime;

public abstract class Question<T> implements Gradable, Comparable<Question<?>> {
    //  declarare campuri
    private LocalDateTime timestamp;
    private String typeQuestion;
    private String author;
    private int difficulty;
    private double maxPoints;
    private String textQuestion;
    private T rightAnswer;

    //  constructor
    public Question(LocalDateTime timestamp, String typeQuestion, String author, int difficulty, double maxPoints, String textQuestion, T rightAnswer) {
        this.timestamp = timestamp;
        this.typeQuestion = typeQuestion;
        this.author = author;
        this.difficulty = difficulty;
        this.maxPoints = maxPoints;
        this.textQuestion = textQuestion;
        this.rightAnswer = rightAnswer;
    }

    //  settere si gettere
    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(LocalDateTime timestamp) {
        this.timestamp = timestamp;
    }

    public String getTypeQuestion() {
        return typeQuestion;
    }

    public void setTypeQuestion(String typeQuestion) {
        this.typeQuestion = typeQuestion;
    }

    public String getAutor() {
        return author;
    }

    public void setAutor(String author) {
        this.author = author;
    }

    public int getDifficulty() {
        return difficulty;
    }

    public void setDifficulty(int difficulty) {
        this.difficulty = difficulty;
    }

    public double getMaxPoints() {
        return maxPoints;
    }

    public void setMaxPoints(double maxPoints) {
        this.maxPoints = maxPoints;
    }

    public String getTextQuestion() {
        return textQuestion;
    }

    public void setTextQuestion(String textQuestion) {
        this.textQuestion = textQuestion;
    }

    public T getRightAnswer() {
        return rightAnswer;
    }

    public void setRightAnswer(T rightAnswer) {
        this.rightAnswer = rightAnswer;
    }

    //  metoda abstracta checkAnswer
    public abstract Correctness checkAnswer(T input);

    //  metoda abstracta pentru transformarea raspunsului corect in formatul corespunzator
    public abstract Correctness transfAnswer(String rightAnswer);

    //  metoda pentru ordonare dupa data (timestamp)
    @Override
    public int compareTo(Question<?> question) {
        if (this.getTimestamp().isAfter(question.getTimestamp())) {
            return 1;
        }
        if (this.getTimestamp().isBefore(question.getTimestamp())) {
            return -1;
        }
        //  sortare dupa autor in caz de egalitate
        if (this.getAutor().compareTo(question.getAutor()) > 0) {
            return 1;
        }
        if (this.getAutor().compareTo(question.getAutor()) < 0) {
            return -1;
        }
        return 0;
    }
}