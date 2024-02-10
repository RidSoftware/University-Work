/*
 * Solutions for the SQL Exercises tutorial
 */

-- 1. The ssn, last name and date of birth of all male employees, in name order
SELECT ssn, lastname, dateOfBirth
FROM   DBEmployee
WHERE  gender = 'M'
ORDER BY lastname;
/* 24 rows */

-- 2. Find all the different types of deadline
SELECT DISTINCT dLineType
FROM   DBDeadline;
/* Bid, Intermediate, Final */

-- 3. Find the name of the department managed by David Lee.
SELECT dName
FROM   DBDepartment, DBEmployee
WHERE  mgrSsn = ssn
AND    lastname = 'Lee'
AND    firstnames = 'David';
/* Chemistry */


/*ALTERNTIVE APPROACH*/

SELECT dName
FROM DBDepartment a 
JOIN  DBEmployee b ON  mgrSsn=ssn 
WHERE lastname='Lee' 
AND firstnames='David';


--4. Find the name of projects run by the Physics department
SELECT pName
FROM   DBDepartment, DBProject
WHERE  pdNum = dNum
AND    dName = 'Physics';
/* Mars, Uranus, Venus */

-- 5. How many hours does Sanjay James work on the Jupiter project?
SELECT hours
FROM   DBWorksOn, DBProject, DBEmployee
WHERE  wssn = ssn
AND    wpNum = pNum
AND    lastname = 'James'
AND    firstnames = 'Sanjay'
AND    pname = 'Jupiter';
/* 45 */


/*ALTERNTIVE APPROACH*/

SELECT hours 
FROM DBWorksOn a 
JOIN DBProject b ON a.wpNum=b.pNum 
JOIN DBEmployee c ON c.ssn = a.wssn 
WHERE pname='Jupiter' 
AND lastname='James' 
AND firstnames='Sanjay';



-- 6. Investigate string functions LEFT and CONCAT to find the employee names in the format lastname comma space initial e.g. Smith, J. Don’t put a space between the function name and the open bracket. http://dev.mysql.com/doc/refman/5.6/en/string-functions.html
SELECT CONCAT(lastname, ', ', LEFT(firstnames, 1) )
FROM   DBEmployee;
/* 38 rows */

//SQLlite version
SELECT lastname || ', ' || substr(firstnames, 1,1) 
FROM   DBEmployee;




-- 7. Create a view to summarise employee names and ssn, the number and name of their department and the locations that this department is based in. Use this in the next question, and afterwards if useful.
CREATE VIEW DBEmpLocs AS (
    SELECT ssn, firstnames, lastname, empdNum, dName, loc
    FROM   DBEmployee, DBDepartment, DBLocation
    WHERE  empdNum = dNum
    AND    dNum = ldNum);
    
	
--without ( ) if using SQLite


 
-- 8. Use the view to find the locations that each employee might visit (i.e. where their department is located). Display employee names and their locations.
SELECT firstnames, lastname, loc
FROM   DBEmpLocs;
/* 39 rows */

-- 9. Find the number and name of all departments, except those managed by Lee or Kaur.
SELECT dNum, dName
FROM   DBDepartment
WHERE  dNum NOT IN
      (SELECT empdNum
       FROM   DBEmployee, DBDepartment
       WHERE  mgrSsn = ssn
       AND    (lastname = 'Lee' OR lastname = 'Kaur') );
/* Returns all departments except 4 or 5 */


/* ALTERNATIVE WITHOUT A JOIN */

SELECT dNum, dName
from DBDepartment 
WHERE mgrSsn NOT IN 
(
SELECT ssn FROM DBEmployee 
WHERE lastname IN ('Lee','Kaur')
)
or mgrSsn IS NULL
;



-- 10. Find the name of each employee and the name of his or her supervisor
SELECT E.firstnames, E.lastname, S.firstnames, S.lastname
FROM   DBEmployee E, DBEmployee S
WHERE  E.supSsn = S.ssn;
/* 32 rows */

-- 11. Find the ssn number and name of all the employees, including, for managers, the department number and name of the department that they manage. Put this in one query.
SELECT E.ssn, E.firstnames, E.lastname, D.dNum, D.dName
FROM DBEmployee E LEFT JOIN DBDepartment D ON D.mgrssn = E.ssn;
/* 38 rows with lots of NULLs */

-- 12. Find the names of employees who do not have a supervisor
SELECT E.firstnames, E.lastname
FROM   DBEmployee E
WHERE  E.supSsn is NULL;
/* 6 rows */

/*** AGGREGATE FUNCTIONS ***/

-- 13. Find the total number of different locations (make sure you are not counting duplicates, the distinct keyword can be used within the count function)
SELECT COUNT(DISTINCT loc)
FROM   DBLocation;
/* There are 3 distinct locations */

-- 14. Find how many hours are worked on for each project. Show project number, name and total hours worked.
SELECT pNum, pName, SUM(hours) AS worked
FROM   DBProject, DBWorksOn
WHERE  pNum = wpNum
GROUP BY pNum;
/* 9 groups */

-- 15. For each department, show the department name and the number of projects worked on, only for departments with more than one project.
SELECT dNum, COUNT(pNum) AS projectNumbers
FROM   DBProject, DBDepartment
WHERE  dNum = pdNum
GROUP BY dNum
HAVING COUNT(pNum) > 1;
/* 4 rows */

-- 16. Find the average number of employees associated with each department. You can use the string FORMAT function to show only 1 decimal place in the result.
SELECT FORMAT(AVG(C.countEmp),1)
FROM  (SELECT COUNT(ssn) countEmp , empdNum
       FROM DBEmployee
       GROUP BY empdNum) C;
/* 6.3 */

/*** UPDATING THE DATA. ***/

-- 17. Increase the salary by 1000 for the employee David Lee. Display it before and after to prove it worked
SELECT salary
FROM   DBEmployee
WHERE  lastname = 'Lee'
AND    firstnames = 'David';
/* 18000 */

UPDATE DBEmployee
SET salary = salary + 1000
WHERE lastname = 'Lee'
AND   firstnames = 'David';
/* 1 row affected */

SELECT salary
FROM   DBEmployee
WHERE  lastname = 'Lee'
AND    firstnames = 'David';
/* 19000 */

-- 18. Jane Barr now works for 10 hours on project Jupiter, prove this worked.
SELECT sum(hours)
FROM   DBWorksOn
WHERE  wssn IN (SELECT ssn
                FROM   DBEmployee
                WHERE  lastname = 'Barr'
                AND    firstNames = 'Jane')
AND    wpNum IN (SELECT pNum
                 FROM   DBProject
                 WHERE  pName = 'Jupiter');
/* NULL */

INSERT INTO DBWorksOn
VALUES (300,3,10);
/* 1 row affected */

SELECT sum(hours)
FROM   DBWorksOn
WHERE  wssn IN (SELECT ssn
                FROM   DBEmployee
                WHERE  lastname = 'Barr'
                AND    firstNames = 'Jane')
AND    wpNum IN (SELECT pNum
                 FROM   DBProject
                 WHERE  pName = 'Jupiter');
/* 10 */

-- 19. Try to delete department 3.
DELETE FROM DBDepartment
WHERE  dNum = 3;
/* This delete fails because there are employees and projects and locations with foreign keys pointing to the department */

-- 20. Add a new department 13. Then delete department number 13.
INSERT INTO DBDepartment
VALUES (13, 'Testing', NULL, NULL);
/* 1 row affected */
DELETE FROM DBDepartment
WHERE  dNum = 13;
/* 1 row affected */
/* This delete works because there are no other rows in other tables with foreign keys pointing to the branch. */

-- 21. Change the department number from 1 to 10. This should cascade into employees and projects. Check this worked with a query, then change back to 1.
SELECT empdNum, COUNT(*)
FROM   DBEmployee
GROUP BY empdNum;
/* Note no department 10 and department 1 has 7 employees */

UPDATE DBDepartment
SET    dNum = 10
WHERE  dNum = 1;
/* 1 row affected */

SELECT empdNum, COUNT(*)
FROM   DBEmployee
GROUP BY empdNum;
/* Note now department 1 and department 10 has 7 employees */

UPDATE DBDepartment
SET    dNum = 1
WHERE  dNum = 10;
/* 1 row affected */

-- 22. Delete the employee with staff number 220 - this should insert null for supervisor for Jane Barr.
SELECT supssn
FROM   DBEmployee
WHERE  lastName = 'Barr'
AND    firstNames = 'Jane';
/* 220 */

DELETE FROM DBEmployee
WHERE  ssn = 220;
/* 1 row affected */

SELECT supssn
FROM   DBEmployee
WHERE  lastName = 'Barr'
AND    firstNames = 'Jane';
/* NULL */
