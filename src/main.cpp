#include <iostream>
#include "functions.h"
#include "functions2.h"
#include "functions3.h"

int main() {
    std::cout << "Features:\n";

    std::cout << "\n1. enciphering\n";
    std::string plainText = "насамомкраюселамироносицкоговсараестаростыпрокофиярасположилисьнаночлегзапоздавшиеохотникиихбылотолькодвоеветеринарныйврачиваниванычиучительгимназиибуркинуиванаиванычабыладовольностраннаядвойнаяфамилиячимшагималайскийкотораясовсемнешлаемуиегововсейгуберниизвалипростопоименииотчествуонжилокологороданаконскомзаводеиприехалтеперьнаохотучтобыподышатьчистымвоздухомучительжегимназиибуркинкаждоелетогостилуграфовпивэтойместностидавноужебылсвоимчеловекомнеспалииваниванычвысокийхудощавыйстариксдлиннымиусамисиделснаружиувходаикурилтрубкуегоосвещалалунабуркинлежалвнутринасенеиегонебыловидновпотемкахрассказывалиразныеисториимеждупрочимговорилиотомчтоженастаростымавраженщиназдороваяинеглупаявовсюсвоюжизньнигденебыладальшесвоегородногоселаникогданевиделанигороданижелезнойдорогиавпоследниедесятьлетвсесиделазапечьюитолькопоночамвыходиланаулицучтожетутудивительногосказалбуркинлюдейодинокихпонатурекоторыекакракотшелышкилиулиткастараютсяуйтивсвоюскорлупунаэтомсветенемалобытьможеттутявлениеатавизмавозвращениектомувременикогдапредокчеловеканебылещеобщественнымживотными";
    auto text = utf16ToInt(plainText);
    auto encryptedText = encrypt(text, 458, 673);
    outputVector(intToUtf16(encryptedText));

    std::cout << "\n2. deciphering\n";
    auto decryptedText = decrypt(encryptedText, 458, 673);
    outputVector(intToUtf16(decryptedText));

    std::cout << "\n3. cryptanalysis of text from resources/encipheredText.txt\n";
    auto cipher = readRawData("../resources/encipheredText.txt");
    auto encryptedData = utf16ToInt(cipher);

    auto mainKey = calcKeys(encryptedData);
    std::cout << "key: " << mainKey.first << " : " << mainKey.second << std::endl;

    auto decryptedData = decrypt(encryptedData, mainKey.first, mainKey.second);
    auto finalData = intToUtf16(decryptedData);
    outputToFile(finalData, "../resources/output.txt");
    std::cout << "\nafter cryptanalysis plain text was saved to resources/output.txt\n";

    return 0;
}
