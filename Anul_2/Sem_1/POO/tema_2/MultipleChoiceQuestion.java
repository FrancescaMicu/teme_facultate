package org.example;

import java.time.LocalDateTime;

public class MultipleChoiceQuestion extends Question<ResponseOption> {
    //  constructor
    public MultipleChoiceQuestion(LocalDateTime timestamp, String typeQuestion, String author, int difficulty, double maxPoints, String textQuestion, ResponseOption rightAnswer) {
        super(timestamp, typeQuestion, author, difficulty, maxPoints, textQuestion, rightAnswer);
    }

    //  metoda transfAnswer
    @Override
    public Correctness transfAnswer(String rightAnswer) {
        return checkAnswer(ResponseOption.valueOf(rightAnswer));
    }

    //  metoda checkAnswer
    @Override
    public Correctness checkAnswer(ResponseOption input) {
        if (getRightAnswer().equals(input)) {
            return Correctness.CORRECT;
        }
        return Correctness.INCORRECT;
    }

    //  metoda procentQuestion
    @Override
    public double procentQuestion(Correctness correctness) {
        if (correctness.equals(org.example.Correctness.CORRECT)) {
            return 1.0;
        }
        return 0.0;
    }
}