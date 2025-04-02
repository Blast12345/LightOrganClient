import json
import subprocess

def run_pio_check():
    result = subprocess.run(["pio", "check", "--json-output"], capture_output=True, text=True)
    return json.loads(result.stdout)

def format(defect):
    file = defect["file"]
    line = defect["line"]
    column = defect.get("column", 1)
    category = defect.get("category", "warning")
    message = defect["message"].strip()
    check_id = defect.get("id", "")
    return f"{file}:{line}:{column}: {category}: {message} [{check_id}]"

if __name__ == "__main__":
    try:
        environments = run_pio_check()
        for env in environments:
            for defect in env.get("defects", []):
                formattedDefect = format(defect)
                print(formattedDefect)
    except Exception as e:
        print(f"# Failed to parse check results: {e}")
