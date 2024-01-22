;; Elias Woldie
;; Class (CECS 342-07)
;; Project Name (Prog 4 – Fibonacci Solatire)
;; 11/09/2023

;; I certify that this program is my own original work. I did not copy any part of this program from
;; any other source. I further certify that I typed each and every line of code in this program.

(defparameter *deck* nil)

(defun create-deck ()
  "Creates a new deck of 52 playing cards."
  (loop for suit in '(H D C S) ; Hearts, Diamonds, Clubs, Spades
        for face in '(A 2 3 4 5 6 7 8 9 10 J Q K)
        collect (cons face suit)))

(defun display-deck ()
  "Prints out the current deck of cards, showing all cards side by side."
  (dolist (card *deck*)
    (format t "~A~A " (car card) (cdr card)))
  (format t "~%"))

(defun shuffle-deck (deck)
  "Randomly shuffles the deck of cards."
  (if (null deck)
      (progn
        (format t "Cannot shuffle an empty deck.~%")
        nil)
      (let ((shuffled-deck (copy-list deck)))
        (loop for i from (1- (length shuffled-deck)) downto 1 do
              (rotatef (nth i shuffled-deck) (nth (random (1+ i)) shuffled-deck)))
        shuffled-deck)))

(defun card-value (card)
  "Returns the value of a card for the sum."
  (case (car card)
    (J Q K 10)    
    (A 1)         
    (otherwise    
     (car card))))

(defun is-fibonacci? (n)
  "Checks if the provided number n is a Fibonacci number."
  (let ((a 0) (b 1) (temp 0))
    (loop while (< a n) do
      (setf temp b b (+ a b) a temp))
    (= a n)))

(defun play-game ()
  "Runs a single game of Fibonacci Solitaire."
  (setf *deck* (shuffle-deck (create-deck)))
  (let ((sum 0)
        (fib-count 0)
        (pile '())
        (pile-count 0) 
        (game-won nil))
    (dolist (card *deck*)
      (push card pile)
      (incf sum (card-value card))
      (if (is-fibonacci? sum)
          (progn
            (incf fib-count)
            (format t "~{~A~}, Fibo: ~A~%" (mapcar #'print-card (reverse pile)) sum)
            (setf pile '()) 
            (setf sum 0)
            (incf pile-count)) 
        (format t "~{~A~}, Fibo: ~A~%" (mapcar #'print-card (reverse pile)) sum)))
    (unless (null pile) (incf pile-count)) 
    (setf game-won (and (is-fibonacci? sum) (null pile))) 
    (format t "~A in ~A pile~:P with ~A Fibonacci pile~:P!~%" (if game-won "Winner" "Loser") pile-count pile-count fib-count fib-count)
    (values game-won fib-count)))

(defun display-menu ()
  "Displays the game menu to the player."
  (terpri)
  (format t "Welcome to Fibonacci Solitaire!~%")
  (format t "1) New Deck~%")
  (format t "2) Display Deck~%")
  (format t "3) Shuffle Deck~%")
  (format t "4) Play Solitaire~%")
  (format t "5) Play until Win~%")
  (format t "6) Exit~%"))

(defun print-card (card)
  "Formats a card for printing by combining the face and suit."
  (format nil "~A~A " (car card) (cdr card)))

(defun main ()
  "Main function to start the game."
  (loop
    (display-menu)
    (let ((choice (read)))
      (case choice
        (1 (setf *deck* (create-deck))
           (format t "New deck created.~%"))
        (2 (display-deck))
        (3 (if (null *deck*)
               (format t "Cannot shuffle an empty deck.~%")
               (progn
                 (setf *deck* (shuffle-deck *deck*))
                 (format t "Shuffled deck:~%")
                 (display-deck)))) 
        (4 (play-game))
        (5 (play-until-win))
        (6 (return-from main (format t "Exiting game. Goodbye!~%")))
        (otherwise (format t "Invalid choice. Try again.~%"))))))

(main)
