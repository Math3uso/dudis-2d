const { execSync } = require("child_process");
const fs = require("fs");
const path = require("path");

function runProject(plataform, options) {
    const cwd = process.cwd();
    const buildDir = path.join(cwd, "build");

    let json = "";
    json = fs.readFileSync(path.join(cwd, "dd-config.json"), "utf-8", json);
    const config = JSON.parse(json);

    const exeName = plataform === "win32"
        ? `${config.projectName}.exe`
        : config.projectName;


    if (options.force) {
        buildProject();
    }
    execSync(`cmake --build "${buildDir}" --config Release`, { stdio: "inherit" });

    const binPath = path.join(buildDir, config.projectName, "bin", exeName);

    if (!fs.existsSync(binPath)) {
        console.error("❌ Executável não encontrado:", binPath);
        process.exit(1);
    }

    execSync(`"${binPath}"`, { stdio: "inherit" });

}

function buildProject() {
    console.log("🔧 Gerando build...");
    const cwd = process.cwd();
    console.log(cwd);

    const cmakeFile = path.join(cwd, "CMakeLists.txt");
    const buildDir = path.join(cwd, "build");

    if (!fs.existsSync(buildDir)) fs.mkdirSync(buildDir);

    if (!fs.existsSync(cmakeFile)) {
        console.error("❌ Nenhum CMakeLists.txt encontrado no diretório atual.");
        process.exit(1);
    }

    execSync(`cmake -S "${cwd}" -B "${buildDir}"`, { stdio: "inherit" });

    console.log("build finalizado com sucesso ✅");

}

module.exports = {
    runProject,
    buildProject
}