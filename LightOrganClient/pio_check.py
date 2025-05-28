import json
import subprocess
import sys
from vscode_problem import VSCodeProblem, VSCodeSeverity

def run():
    try:
        for defects in get_defects():
            problem = create_problem(defects)
            print(problem.toString())
    except Exception as e:
        print(f"# Failed to parse check results: {e}")
        sys.exit(1)

def get_defects():
    result = subprocess.run(["pio", "check", "--json-output"], capture_output=True, text=True)
    environments = json.loads(result.stdout)
    
    defects = []
    for env in environments:
        defects.extend(env.get("defects", []))

    return defects


def create_problem(defect):
    try:
        file = defect["file"]
        line = int(defect["line"])
        column = int(defect["column"])
        severity = normalize_severity(defect["category"])
        message = defect["message"].strip()
        code = defect["id"]
    except KeyError as e:
        raise ValueError(f"Missing required field in defect: {e} | defect: {defect}")
    except Exception as e:
        raise ValueError(f"Error parsing defect: {e} | defect: {defect}")

    return VSCodeProblem(
        file,
        line,
        column,
        severity,
        message,
        code
    )

def normalize_severity(category):
    if category.casefold() == "error":
        return VSCodeSeverity.ERROR
    elif category.casefold() == "info":
        return VSCodeSeverity.INFO
    else:
        return VSCodeSeverity.WARNING

if __name__ == "__main__":
    run()