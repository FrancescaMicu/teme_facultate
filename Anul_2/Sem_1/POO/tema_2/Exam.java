package org.example;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class Exam {
    //  declarare campuri
    private static final DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("dd-MM-yyyy-HH-mm");
    private LocalDateTime timestamp;
    private String nameExam;
    private LocalDateTime startDate;
    private LocalDateTime endDate;
    private TreeSet<Question<?>> questionsSortByDate;
    private TreeSet<Question<?>> questionsSortByDiff;
    private HashMap<Student, Double> students;

    //  constructor
    public Exam(LocalDateTime timestamp, String nameExam, LocalDateTime startDate, LocalDateTime endDate) {
        this.timestamp = timestamp;
        this.nameExam = nameExam;
        this.startDate = startDate;
        this.endDate = endDate;
        this.questionsSortByDate = new TreeSet<>();
        this.questionsSortByDiff = new TreeSet<>(new QuestionComparator());
        this.students = new HashMap<>();
    }

    //  settere si gettere
    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(LocalDateTime timestamp) {
        this.timestamp = timestamp;
    }

    public String getNameExam() {
        return nameExam;
    }

    public void setNameExam(String nameExam) {
        this.nameExam = nameExam;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDateTime startDate) {
        this.startDate = startDate;
    }

    public LocalDateTime getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDateTime endDate) {
        this.endDate = endDate;
    }

    public TreeSet<Question<?>> getQuestionsByDate() {
        return questionsSortByDate;
    }

    public TreeSet<Question<?>> getQuestionsSortByDiff() {
        return questionsSortByDiff;
    }

    //  metoda addQuestion
    public void addQuestion(Question<?> newQuestion) {
        this.questionsSortByDate.add(newQuestion);
        this.questionsSortByDiff.add(newQuestion);
    }

    //  metoda pentru afisare intrebari ordonate dupa data
    public void printQuestionsAfterTimestamp(String path, LocalDateTime cmdTimeStamp) throws FileNotFoundException {
        PrintWriter writeFile = null;
        String fileName = path + "questions_history_" + nameExam + "_" + cmdTimeStamp.format(timeFormat) + ".out";
        try {
            writeFile = new PrintWriter(fileName);
            for (Question<?> question : questionsSortByDate) {
                writeFile.println(question.getTimestamp().format(timeFormat) + " | " + question.getTextQuestion() + " | " +  question.getRightAnswer() + " | " + question.getDifficulty() + " | " + question.getMaxPoints() + " | " + question.getAutor());
            }
        } finally {
            if (writeFile != null) {
                writeFile.close();
            }
        }
    }

    //  metoda pentru afisare intrebari ordonate dupa dificultate
    public void printQuestionsAfterDifficulty(String path, LocalDateTime cmdTimeStamp) throws FileNotFoundException {
        String fileName = path + "print_exam_" + nameExam + "_" + cmdTimeStamp.format(timeFormat) + ".out";
        PrintWriter writeFile = null;
        try {
            writeFile = new PrintWriter(fileName);
            for (Question<?> question : questionsSortByDiff) {
                writeFile.println(question.getMaxPoints() + " | " + question.getTextQuestion() + " | " + question.getDifficulty() + " | "+ question.getRightAnswer());
            }
        } finally {
            if  (writeFile != null) {
                writeFile.close();
            }
        }
    }

    //  metoda pentru generare fisier
    public void printResultsAnytime(String path, LocalDateTime cmdTimeStamp) throws FileNotFoundException {
        ArrayList<Student> studentsOrder = new ArrayList<>(students.keySet());
        //  sortare dupa nume alfabetic
        Collections.sort(studentsOrder);
        String fileName =  path + "exam_report_" + nameExam + "_" + cmdTimeStamp.format(timeFormat) + ".out";
        PrintWriter writeFile = null;
        try {
            writeFile = new PrintWriter(fileName);
            for (Student student : studentsOrder) {
                writeFile.printf(student.getName() + " | " + "%.2f", student.calcScoreCurrExam(nameExam));
                writeFile.println();
            }
        } finally {
            if (writeFile != null) {
                writeFile.close();
            }
        }
    }

    //  metoda pentru submit_exam
    public double studAnswersChecked(Student student, ArrayList<String> answers, LocalDateTime cmdTimeStamp) throws SubmissionOutsideTimeIntervalException  {
        //  verificare daca examenul a fost trimis in perioada alocata
        if (cmdTimeStamp.isAfter(endDate) || cmdTimeStamp.isBefore(startDate)) {
            students.put(student, 0.0);
            throw new SubmissionOutsideTimeIntervalException(cmdTimeStamp, student.getName(), "Submission outside of time interval for student ");
        }
        double totalPoints = 0;
        int i = 0;
        for (Question<?> question : questionsSortByDiff) {
            Correctness questionAnswer = null;
            //  apel checkAnswer in functie de tipul rightAnswer
            questionAnswer = question.transfAnswer(answers.get(i));
            if (questionAnswer != null) {
                totalPoints += question.getMaxPoints() * question.procentQuestion(questionAnswer);
            }
            i++;
        }
        students.put(student, totalPoints);
        return totalPoints;
    }
}

//  clasa pentru sortare dupa dificultate
class QuestionComparator implements Comparator<Question<?>> {
    @Override
    public int compare(Question<?> question1, Question<?> question2) {
        if (question1.getDifficulty() > question2.getDifficulty()) {
            return 1;
        }
        if (question1.getDifficulty() < question2.getDifficulty()) {
            return -1;
        }
        //  sortare pentru caz de egalitate
        if (question1.getTextQuestion().compareTo(question2.getTextQuestion()) > 0) {
            return 1;
        }
        if (question1.getTextQuestion().compareTo(question2.getTextQuestion()) < 0) {
            return -1;
        }
        return 0;
    }
}

//  folosita pentru sortarea initiala ceruta (descrescator dupa punctajul studentului)
//  pana la urma, in teste, a fost ceruta sortarea doar alfabetic
/*
class StudentsComparator implements Comparator<Student> {
    //  declarare campuri
    private HashMap<Student, Double> students;

    //  constructor
    public StudentsComparator(HashMap<Student, Double> students) {
        this.students = students;
    }

    @Override
    public int compare(Student student1, Student student2) {
        if (students.get(student1) < students.get(student2)) {
            return 1;
        }
        if (students.get(student1) > students.get(student2)) {
            return -1;
        }
        //  caz de egalitate
        if (student1.getName().compareTo(student2.getName()) > 0) {
            return 1;
        }
        if (student1.getName().compareTo(student2.getName()) < 0) {
            return -1;
        }
        return 0;
    }
}
 */
