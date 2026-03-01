package org.example;

import java.time.LocalDateTime;

public class FillInTheBlankQuestion extends Question<String> {
    //  constructor
    public FillInTheBlankQuestion(LocalDateTime timestamp, String typeQuestion, String author, int difficulty, double maxPoints, String textQuestion, String rightAnswer) {
        super(timestamp, typeQuestion, author, difficulty, maxPoints, textQuestion, rightAnswer);
    }

    //  metoda transfAnswer
    @Override
    public Correctness transfAnswer(String rightAnswer) {
        return checkAnswer(rightAnswer);
    }

    //  metoda checkAnswer
    @Override
    public Correctness checkAnswer(String input) {
        if (getRightAnswer().equals(input)) {
            return org.example.Correctness.CORRECT;
        }
        int nrLettInp = input.length();
        int nrLettRigAns = getRightAnswer() .length();
        if ((nrLettInp <= nrLettRigAns + 2 && nrLettInp >= nrLettRigAns - 2) && (input.contains(getRightAnswer()) || getRightAnswer().contains(input))) {
            return org.example.Correctness.PART_CORRECT;
        }
        return org.example.Correctness.INCORRECT;
    }

    //  metoda procentQuestion
    @Override
    public double procentQuestion(Correctness correctness) {
        if (correctness.equals(org.example.Correctness.CORRECT)) {
            return 1.0;
        }
        if (correctness.equals(org.example.Correctness.INCORRECT)) {
            return 0.0;
        }
        return 0.5;
    }
}