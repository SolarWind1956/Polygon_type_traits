#pragma once
#include <type_traits>
#include <iostream>
using std::cout; using std::endl;
#include "../color_output.hpp"

namespace chat_gpt_seh {

template <typename U>
void triviality_tester(const char* name)
{
    using namespace color_output;

    cout << bright_yellow << "\n========== Triviality Tester ==========" << reset << "\n";
    cout << cyan << "Type: " << reset << name << "\n\n";

    // -----------------------
    // HIGH-LEVEL CLASSIFICATION
    // -----------------------
    bool is_trivial               = std::is_trivial_v<U>;
    bool is_trivially_copyable    = std::is_trivially_copyable_v<U>;
    bool is_standard_layout       = std::is_standard_layout_v<U>;
    bool is_pod                   = std::is_pod_v<U>;  // historical

    cout << bright_white << "[ High-level classification ]\n" << reset;
    auto row = [&](const char* label, bool v)
    {
        cout << "  " << std::left << std::setw(32) << label
                  << (v ? green : red)
                  << (v ? "Yes" : "No")
                  << reset << "\n";
    };

    row("std::is_trivial_v",                is_trivial);
    row("std::is_trivially_copyable_v",     is_trivially_copyable);
    row("std::is_standard_layout_v",        is_standard_layout);
    row("std::is_pod_v (historical)",       is_pod);

    cout << "\n";


    // -----------------------
    // SPECIAL MEMBER FUNCTIONS
    // -----------------------
    bool triv_def_ctor   = std::is_trivially_default_constructible_v<U>;
    bool triv_dtor       = std::is_trivially_destructible_v<U>;
    bool triv_copy_ctor  = std::is_trivially_copy_constructible_v<U>;
    bool triv_move_ctor  = std::is_trivially_move_constructible_v<U>;
    bool triv_copy_asg   = std::is_trivially_copy_assignable_v<U>;
    bool triv_move_asg   = std::is_trivially_move_assignable_v<U>;

    cout << bright_white << "[ Special member triviality ]\n" << reset;

    row("Default constructor trivial",       triv_def_ctor);
    row("Destructor trivial",                triv_dtor);
    row("Copy constructor trivial",          triv_copy_ctor);
    row("Move constructor trivial",          triv_move_ctor);
    row("Copy assignment trivial",           triv_copy_asg);
    row("Move assignment trivial",           triv_move_asg);

    cout << "\n";


    // -----------------------
    // USER-PROVIDED DETECTION (approximate, heuristic)
    // -----------------------
    // Эти проверки не определяются стандартом напрямую.
    // Но если default ctor НЕ тривиальный, но exists → он user-provided.
    // Это эвристика, но 99% случаев правильно работает.

    cout << bright_white << "[ Heuristics: user-provided members ]\n" << reset;

    auto user_row = [&](const char* label, bool trivial, bool is_constructible)
    {
        // приблизительно: если существует, но не trivial → user-provided
        bool user_provided = (is_constructible && !trivial);

        cout << "  " << std::left << std::setw(32) << label
                  << (user_provided ? yellow : green)
                  << (user_provided ? "USER-PROVIDED" : "OK")
                  << reset << "\n";
    };

    user_row("Default constructor", triv_def_ctor,
             std::is_default_constructible_v<U>);

    user_row("Destructor", triv_dtor,
             std::is_destructible_v<U>);

    user_row("Copy constructor", triv_copy_ctor,
             std::is_copy_constructible_v<U>);

    user_row("Move constructor", triv_move_ctor,
             std::is_move_constructible_v<U>);

    user_row("Copy assignment", triv_copy_asg,
             std::is_copy_assignable_v<U>);

    user_row("Move assignment", triv_move_asg,
             std::is_move_assignable_v<U>);

    cout << "\n";


    // -----------------------
    // SUMMARY
    // -----------------------
    cout << bright_white << "[ Summary ]\n" << reset;

    cout << "  Type is ";
    if (is_trivial)
        cout << green << "TRIVIAL\n" << reset;
    else
        cout << red << "NON-TRIVIAL\n" << reset;

    cout << "  Full POD (trivial + standard layout): ";
    if (is_trivial && is_standard_layout)
        cout << green << "YES\n" << reset;
    else
        cout << red << "NO\n" << reset;