import subprocess
import sys
import re
from vscode_problem import VSCodeProblem, VSCodeSeverity

def run():
    try:
        for defect in get_defects():
            problem = create_problem(defect)
            print(problem.toString())
    except Exception as e:
        print(f"# Failed to parse check results: {e}")
        sys.exit(1)

def get_defects():
    result = subprocess.run(
        [
            "cppcheck",
            "src/",
            "--enable=all",
            "--inline-suppr",
            "--suppress=missingIncludeSystem",
            "--suppress=checkersReport",
            "--template={file}:{line}:{column}: {severity}: {message} [{id}]"
        ],
        stderr=subprocess.PIPE,
        text=True
    )
    return result.stderr.splitlines()

def create_problem(defect):
    match = re.match(r"^(.*):(\d+):(\d+): (\w+): (.*) \[(.*)\]$", defect)

    if not match:
        raise ValueError(f"Could not parse defect line: {defect}")
    
    file, line, column, severity, message, code = match.groups()

    return VSCodeProblem(
        file,
        int(line), 
        int(column),
        normalize_severity(severity),
        message,
        code)

def normalize_severity(severity):
    if severity.casefold() == "error":
        return VSCodeSeverity.ERROR 
    if severity.casefold() == "information":
        return VSCodeSeverity.INFO
    else:
        return VSCodeSeverity.WARNING 

if __name__ == "__main__":
    run()