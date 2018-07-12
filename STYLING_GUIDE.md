# Styling Guide

**Note that we were talking about C++**

**tl;dr: Every code should pass the cpplint provided in the repo. Run test.cpp to test on your own.**

## Main

We might be following [Google's Styling Guide](https://github.com/google/styleguide).

The official cppguide is [on Google's Github Site](http://google.github.io/styleguide/cppguide.html).

We can also follow a [zh-google-styleguide](http://zh-google-styleguide.readthedocs.org/en/latest/google-cpp-styleguide/) if you find it hard to remember all the English guidelines.

A tool called [cpplint](https://pypi.python.org/pypi/cpplint) can be used to help your check your codes. Also at [cpplint.py](https://github.com/google/styleguide/blob/gh-pages/cpplint/cpplint.py).

Something else [for emacs](https://raw.githubusercontent.com/google/styleguide/gh-pages/google-c-style.el).

You might want to take a look at [STYLING_ASSISTANCE.md](STYLING_ASSISTANCE.md)

Here are something you might forget:

- [ ] 将函数变量尽可能置于最小作用域内, 并在变量声明时进行初始化
- [ ] 注意别在循环犯大量构造和析构的低级错误
- [ ] 在类中使用特定的声明顺序:`public:`在`private:`之前, 成员函数在数据成员 (变量) 前
- [ ] 倾向编写简短, 凝练的函数
- [ ] [所有按引用传递的参数必须加上 const](http://zh-google-styleguide.readthedocs.org/en/latest/google-cpp-styleguide/others/)
- [ ] 只在定义移动构造函数与移动赋值操作时使用右值引用. 不要使用 `std::forward`
- [ ] 我们不允许使用缺省函数参数，少数极端情况除外。尽可能改用函数重载
- [ ] 我们不使用 C++ 异常
- [ ] 只在记录日志时使用流（`string`之类的除外）
- [ ] 对于迭代器和其他模板对象使用前缀形式`(++i)`的自增, 自减运算符
- [ ] 我们强烈建议你在任何可能的情况下都要使用`const`. 此外有时改用 C++11 推出的`constexpr`更好。在 C++11 里，用`constexpr`来定义真正的常量，或实现常量初始化
- [ ] 使用断言来指出变量为非负数, 而不是使用无符号型
- [ ] 代码应该对 64 位和 32 位系统友好. 处理打印, 比较, 结构体对齐时应切记
- [ ] **使用宏时要非常谨慎, 尽量以内联函数, 枚举和常量代替之**
- [ ] 整数用 0, 实数用 0.0, 指针用`nullptr`或`NULL`, 字符 (串) 用`'\0'`
- [ ] 用 auto 绕过烦琐的类型名，只要可读性好就继续用，别用在局部变量之外的地方
- [ ] 函数命名，变量命名，文件命名要有描述性；少用缩写。尽可能给有描述性的命名。文件名要全部小写, 可以包含下划线 (\_) 。类型名称的每个单词首字母均大写。变量名一律小写, 单词之间用下划线连接. 类的成员变量以下划线结尾, 但结构体的就不用。在全局或类里的常量名称前加`k`: kDaysInAWeek. 且除去开头的`k`之外每个单词开头字母均大写。常规函数使用大小写混合, 取值和设值函数则要求与变量名匹配。
- [ ] 注释虽然写起来很痛苦, 但对保证代码可读性至关重要。注释固然很重要, 但最好的代码本身应该是自文档化。使用`//`或`/* */`, 统一就好。在每一个文件开头加入版权公告, 然后是文件内容描述。（参考[TEMPLATE.CPP](TEMPLATE.CPP)）每个类的定义都要附带一份注释, 描述类的功能和用法.函数声明处注释描述函数功能; 定义处描述函数实现.通常变量名本身足以很好说明变量用途. 某些情况下, 也需要额外的注释说明.对于代码中巧妙的, 晦涩的, 有趣的, 重要的地方加以注释.注意 永远不要 用自然语言翻译代码作为注释. 要假设读代码的人 C++ 水平比你高, 即便他/她可能不知道你的用意.对那些临时的, 短期的解决方案, 或已经够好但仍不完美的代码使用`TODO`注释.`TODO`注释要使用全大写的字符串`TODO`, 在随后的圆括号里写上你的大名, 邮件地址, 或其它身份标识. 冒号是可选的.
- [ ] 每一行代码字符数不超过 80.如果一行注释包含了超过 80 字符的命令或 URL, 出于复制粘贴的方便允许该行超过 80 字符.尽量不使用非 ASCII 字符, 使用时必须使用`UTF-8` 编码.**只使用空格, 每次缩进 2 个空格.**
- [ ] 返回类型和函数名在同一行, 参数也尽量放在同一行，如果放不下就对形参分行。**左圆括号总是和函数名在同一行;**函数名和左圆括号间没有空格;圆括号与参数间没有空格;左大括号总在最后一个参数同一行的末尾处;右大括号总是单独位于函数最后一行，或者与左大括号同一行。右大括号和左大括号间总是有一个空格;函数声明和定义中的所有形参必须有命名且一致;所有形参应尽可能对齐;**缺省缩进为 2 个空格;换行后的参数保持 4 个空格的缩进;**如果有些参数没有用到, 在函数定义处将参数名注释起来:要么一行写完函数调用，要么在圆括号里对参数分行，要么参数另起一行且缩进四格。如果没有其它顾虑的话，尽可能精简行数，比如把多个参数适当地放在同一行里。倾向于不在圆括号内使用空格. 关键字 if 和 else 另起一行.
- [ ] 如果语句中某个`if-else`分支使用了大括号的话, 其它分支也必须使用.`switch`语句可以使用大括号分段，以表明`cases`之间不是连在一起的。在单语句循环里，括号可用可不用。空循环体应使用`{}`或 `continue`.句点或箭头前后不要有空格. 指针/地址操作符`(*, &)`之后不能有空格.如果一个布尔表达式超过 标准行宽, 断行方式要统一一下.`return`表达式里时没必要都用圆括号。**指针／地址操作符与变量名紧邻**
- [ ] **规则有特例**
- [ ] **运用常识和判断力, 并保持一致**

## Recommended Sublime Settings

Open a `.cpp` file

GOTO `Preferences`-->`Settings-More`-->`Syntax Specific-User`

You shall be editing `c++.sublime-settings` as below:

```json
{
  "tab_size": 2,
  "translate_tabs_to_spaces": true,
  "line_numbers": true,
  "word_wrap": true,
  "wrap_width": 80,
  "match_brackets": true
}
```

## Other Notes(Not forced)

It might be a good idea to add empty lines into where you find necessary to make things clear.
