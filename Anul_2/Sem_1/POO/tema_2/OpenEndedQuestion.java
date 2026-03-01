package org.example;

import java.time.LocalDateTime;

public class OpenEndedQuestion extends Question<String> {
    //  constructor
    public OpenEndedQuestion(LocalDateTime timestamp, String typeQuestion, String author, int difficulty, double maxPoints, String textQuestion, String rightAnswer) {
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
            return Correctness.CORRECT;
        }
        int nrLettInp = input.length();
        int nrLettRigAns = getRightAnswer() .length();
        //  calculare marja de eroare pentru raspuns partial corect
        int err = (int)Math.round((30.0/100) * nrLettRigAns);
        if ((nrLettInp <= nrLettRigAns + err && nrLettInp >= nrLettRigAns - err) && (input.contains(getRightAnswer()) || getRightAnswer().contains(input))) {
            return Correctness.PART_CORRECT;
        }
        return Correctness.INCORRECT;
    }

    //  metoda procentQuestion
    @Override
    public double procentQuestion(Correctness correctness) {
        if (correctness.equals(Correctness.CORRECT)) {
            return 1.0;
        }
        if (correctness.equals(Correctness.INCORRECT)) {
            return 0.0;
        }
        return 0.7;
    }
}